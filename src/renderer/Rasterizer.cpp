#include "renderer/Rasterizer.h"
#include "renderer/geometry/Line.h"
#include "renderer/geometry/Triangle.h"
#include "utility/print.h"
#include "utility/time/Stopwatch.h"

#include <glm/gtc/matrix_access.hpp>

#include <fstream>
#include <cmath>
#include <tuple>
#include <utility>
#include <algorithm>

#include <omp.h>

namespace cgl
{



inline Vec3 divideByW(const Vec4 vec){
    return Vec3(
        vec.x / vec.w,
        vec.y / vec.w,
        vec.z / vec.w
    );
}

void Rasterizer::setMatrices(const Mat4& view, const Mat4& projection){
    m_modelview_matrix = view;
    m_projection_matrix = projection;
    m_view_projection_matrix = projection * view;
}

enum ClippingPlane{
    LEFT,
    RIGHT,
    BOTTOM,
    TOP,
    NEAR,
    FAR
};

template<ClippingPlane P>
inline bool isOut(const Vertex& v){
    if constexpr(P == ClippingPlane::LEFT){
        return v.pos.x < -v.pos.w;
    }
    if constexpr(P == ClippingPlane::RIGHT){
        return v.pos.x >  v.pos.w;
    }
    if constexpr(P == ClippingPlane::BOTTOM){
        return v.pos.y < -v.pos.w;
    }
    if constexpr(P == ClippingPlane::TOP){
        return v.pos.y >  v.pos.w;
    }
    if constexpr(P == ClippingPlane::NEAR){
        return v.pos.z < -v.pos.w;
    }
    if constexpr(P == ClippingPlane::FAR){
        return v.pos.z >  v.pos.w;
    }
    return false;
}

template<ClippingPlane P>
inline float lineInterpolation(const Vertex& v_1, const Vertex& v_2){
    if constexpr(P == ClippingPlane::LEFT){
        return (-v_2.pos.x - v_2.pos.w) / (v_1.pos.x + v_1.pos.w - v_2.pos.x - v_2.pos.w);
    }
    if constexpr(P == ClippingPlane::RIGHT){
        return (-v_2.pos.x + v_2.pos.w) / (v_1.pos.x - v_1.pos.w - v_2.pos.x + v_2.pos.w);
    }
    if constexpr(P == ClippingPlane::BOTTOM){
        return (-v_2.pos.y - v_2.pos.w) / (v_1.pos.y + v_1.pos.w - v_2.pos.y - v_2.pos.w);
    }
    if constexpr(P == ClippingPlane::TOP){
        return (-v_2.pos.y + v_2.pos.w) / (v_1.pos.y - v_1.pos.w - v_2.pos.y + v_2.pos.w);
    }
    if constexpr(P == ClippingPlane::NEAR){
        return (-v_2.pos.z - v_2.pos.w) / (v_1.pos.z + v_1.pos.w - v_2.pos.z - v_2.pos.w);
    }
    if constexpr(P == ClippingPlane::FAR){
        return (-v_2.pos.z + v_2.pos.w) / (v_1.pos.z - v_1.pos.w - v_2.pos.z + v_2.pos.w);
    }
    return false;
}

template<ClippingPlane P>
inline void clipVertices(Vector<Vertex>& vertices){
    if (vertices.empty()) {
        return;
    }
    vertices.emplace_back(vertices.front());
    for (size_t i = 0; i < vertices.size() - 1; i++){
        Vertex& v_1 = vertices[i];
        Vertex& v_2 = vertices[i + 1];

        bool inc = false;


        if (isOut<P>(v_1)){
            // Cur out, next in, intersect
            if (!isOut<P>(v_2)){
                //
                float mult = lineInterpolation<P>(v_1, v_2);
                vertices.insert(vertices.begin() + i + 1, (v_1 * mult) + (v_2 * (1 - mult)));
                inc = true;
            }
            vertices.erase(vertices.begin() + i);
            i--;
        }
        else{
            // Cur in, next out
            if (isOut<P>(v_2)){
                float mult = lineInterpolation<P>(v_1, v_2);
                vertices.insert(vertices.begin() + i + 1, (v_1 * mult) + (v_2 * (1 - mult)));
                i++;
            }
            // Both in
        }
        i+= inc;
    }
    vertices.pop_back();
}
bool isDegenerateTriangle(const Vec3& point_a, const Vec3& point_b, const Vec3& point_c){
    return (std::abs(point_a.x * (point_b.y - point_c.y) + point_b.x * (point_c.y - point_a.y) + point_c.x * (point_a.y - point_b.y)) < 1);
}

const Rasterizer::DrawStats& Rasterizer::getStats() const{
    return m_stats;
}
void Rasterizer::resetStats(){
    m_stats.discarded_tris = 0;
    m_stats.handled_fragments = 0;
    m_stats.handled_tris = 0;
    m_stats.drawn_fragments = 0;
}
bool Rasterizer::transformVertices(const DrawSettings& settings, unsigned width, unsigned height, Vector<Vertex>& vertices){
    if (vertices.size() != 3){
        throw std::runtime_error("Invalid vertices size");
    }

    bool clip = false;

    /**
     * Transform all vertices to clip space
     * Check by the transformed values if clipping needs to be done
     */
    for (Vertex& v : vertices){
        v.pos = m_modelview_matrix * v.pos;
        v.eye_distance = std::abs(v.pos.z);
        v.pos = m_projection_matrix * v.pos;
        if (!clip && (
            v.pos.w < 0 ||
            v.pos.x < -v.pos.w || v.pos.x > v.pos.w ||
            v.pos.y < -v.pos.w || v.pos.y > v.pos.w ||
            v.pos.z < -v.pos.w || v.pos.z > v.pos.w
        )){
            clip = true;
        }
    }

    /** If clipping is necessary, clip by all 6 faces */
    if (clip){
        clipVertices<ClippingPlane::LEFT>(vertices);
        clipVertices<ClippingPlane::RIGHT>(vertices);
        clipVertices<ClippingPlane::BOTTOM>(vertices);
        clipVertices<ClippingPlane::TOP>(vertices);
        clipVertices<ClippingPlane::NEAR>(vertices);
        clipVertices<ClippingPlane::FAR>(vertices);
    }

    /** If clipping removed all vertices, discard triangle */
    if (vertices.empty()) {
        return false;
    }

    /** Transform vertices to window coordinates. w coord is set to its inverse for later calculations */
    for (Vertex& v : vertices){
        float one_over_w = 1.0f / v.pos.w;
        // Vec4 out = Vec4(((v.pos.x * one_over_w) * width  + width) * 0.5f,
        //                 ((v.pos.y * one_over_w) * height + height) * 0.5f,
        //                 ((v.pos.z * one_over_w) * settings.depth_range_dif) + settings.depth_range_dif,
        //                 one_over_w);

        Vec4 out = Vec4((((v.pos.x * one_over_w) + 1) * (0.5f * settings.vp_info.width) + settings.vp_info.x),
                        (((v.pos.y * one_over_w) + 1) * (0.5f * settings.vp_info.height) + settings.vp_info.y),
                        ((v.pos.z * one_over_w) * settings.depth_range_dif) + settings.depth_range_dif,
                        one_over_w);
        v.pos = out;
    }

    /** If face culling is on, check the triangle and potentially discard*/
    if (settings.cull_face){
        if (settings.cull_mode == GL_FRONT_AND_BACK){
            return false;
        }

        Vec3 line_01 = Vec3{vertices[1].pos} - Vec3{vertices[0].pos};
        Vec3 line_02 = Vec3{vertices[2].pos} - Vec3{vertices[0].pos};

        Vec3 normal = glm::cross(line_01, line_02);

        bool sign = normal.z < 0;

        if (settings.cull_mode == GL_FRONT){
            sign = !sign;
        }
        if (sign && settings.cull_ccw){
            return false;
        }
        else if (!sign && !settings.cull_ccw){
            return false;
        }
    }
    return true;
}

inline Vec4 getBlendFactors(GLenum mode, const ColorCell& src, const ColorCell& dst){
    switch (mode)
    {
        case GL_ZERO:
            return Vec4{0.0f, 0.0f, 0.0f, 0.0f};
            break;
        case GL_ONE:
            return Vec4{1.0f, 1.0f, 1.0f, 1.0f};
            break;
        case GL_SRC_COLOR:
            return src.normalizeRGBA();
            break;
        case GL_ONE_MINUS_SRC_COLOR:
            return Vec4{1.0f, 1.0f, 1.0f, 1.0f} - src.normalizeRGBA();
            break;
        case GL_DST_COLOR:
            return dst.normalizeRGBA();
            break;
        case GL_ONE_MINUS_DST_COLOR:
            return Vec4{1.0f} - dst.normalizeRGBA();
            break;
        case GL_SRC_ALPHA:
            return Vec4{src.normalizeAlpha()};
            break;
        case GL_ONE_MINUS_SRC_ALPHA:
            return Vec4{1.0f} - Vec4{src.normalizeAlpha()};
            break;
        case GL_DST_ALPHA:
            return Vec4{dst.normalizeAlpha()};
            break;
        case GL_ONE_MINUS_DST_ALPHA:
            return Vec4{1.0f} - Vec4{dst.normalizeAlpha()};
            break;
        case GL_SRC_ALPHA_SATURATE:{
            float i = std::min<float>(static_cast<float>(src.alpha),ColorCell::MAX_VALUE - dst.alpha) / ColorCell::MAX_VALUE;
            return Vec4{i, i, i, 1.0f};
            break;
        }
        default:
            throw std::runtime_error("Unsupported blend mode");
            break;
    }
}

inline bool alphaCheck(ColorCell& color, GLenum func, GLclampf val){
    float alpha_norm = color.normalizeAlpha();
    switch (func)
    {
        case GL_NEVER:
            return false;
            break;
        case GL_LESS:
            return alpha_norm < val;
            break;
        case GL_EQUAL:
            return alpha_norm == val;
            break;
        case GL_LEQUAL:
            return alpha_norm <= val;
            break;
        case GL_GREATER:
            return alpha_norm > val;
            break;
        case GL_NOTEQUAL:
            return alpha_norm != val;
            break;
        case GL_GEQUAL:
            return alpha_norm >= val;
            break;
        case GL_ALWAYS:
            return true;
            break;

        default:
            break;
    }
    return false;
}

inline bool depthTest(float stored, float inc, GLenum func){
    switch (func)
    {
        case GL_NEVER:
            return false;
            break;
        case GL_LESS:
            return inc < stored;
            break;
        case GL_EQUAL:
            return inc == stored;
            break;
        case GL_LEQUAL:
            return inc <= stored;
            break;
        case GL_GREATER:
            return inc > stored;
            break;
        case GL_NOTEQUAL:
            return inc != stored;
            break;
        case GL_GEQUAL:
            return inc >= stored;
            break;
        case GL_ALWAYS:
            return true;
            break;

        default:
            break;
    }
    return false;
}

inline bool stencilTest(StencCell stored, StencCell ref, GLenum func){
    switch (func)
    {
        case GL_NEVER:
            return false;
            break;
        case GL_LESS:
            return ref < stored;
            break;
        case GL_EQUAL:
            return ref == stored;
            break;
        case GL_LEQUAL:
            return ref <= stored;
            break;
        case GL_GREATER:
            return ref > stored;
            break;
        case GL_NOTEQUAL:
            return ref != stored;
            break;
        case GL_GEQUAL:
            return ref >= stored;
            break;
        case GL_ALWAYS:
            return true;
            break;

        default:
            break;
    }
    return false;
}

inline void stencilResolve(StencCell* stored, StencCell ref, GLenum func){
    switch (func)
    {
        case GL_KEEP:
            break;
        case GL_ZERO:
            *stored = 0;
            break;
        case GL_REPLACE:
            *stored = ref;
            break;
        case GL_INCR:
            *stored = std::min<int>(*stored + 1, STENC_CELL_MASK);
            break;
        case GL_INCR_WRAP:
            (*stored)++;
            break;
        case GL_DECR:
            *stored = std::max<int>(*stored - 1, 0);
            break;
        case GL_DECR_WRAP:
            (*stored)--;
            break;
        case GL_INVERT:
            *stored = ~(*stored);
            break;

        default:
            break;
    }
}
inline void calcFog(const FogOptions& fog_opts, ColorCell& color, float z){
    float f = 0.0f;
    switch (fog_opts.fog_mode)
    {
        case GL_LINEAR:
            f = (fog_opts.fog_end - z) / (fog_opts.fog_end - fog_opts.fog_start);
            break;

        case GL_EXP:
            f = std::exp(-fog_opts.fog_density * z);
            break;

        case GL_EXP2:
            f = std::exp(std::pow(-fog_opts.fog_density * z, 2));
            break;

        default:
            break;
    }
    f = std::clamp(f, 0.0f, 1.0f);

    color.red   = fog_opts.fog_color_cell.red   + ((color.red   - fog_opts.fog_color_cell.red)   * f);
    color.green = fog_opts.fog_color_cell.green + ((color.green - fog_opts.fog_color_cell.green) * f);
    color.blue  = fog_opts.fog_color_cell.blue  + ((color.blue  - fog_opts.fog_color_cell.blue)  * f);
    color.alpha = fog_opts.fog_color_cell.alpha + ((color.alpha - fog_opts.fog_color_cell.alpha) * f);
}

inline void calcRowRange(float c0, float c0_dx, float c1, float c1_dx, float c2, float c2_dx, int& start, int& end){
    start = std::max({
        c0 >= 0 ? 0 : std::abs(c0 / c0_dx),
        c1 >= 0 ? 0 : std::abs(c1 / c1_dx),
        c2 >= 0 ? 0 : std::abs(c2 / c2_dx),
    });

    c0 += start * c0_dx;
    c1 += start * c1_dx;
    c2 += start * c2_dx;

    end = std::min({
        c0_dx >= 0 ? 2000000 : std::abs(c0 / c0_dx),
        c1_dx >= 0 ? 2000000 : std::abs(c1 / c1_dx),
        c2_dx >= 0 ? 2000000 : std::abs(c2 / c2_dx),
    });
}
inline void addOffset(float& depth, float z_slope, float factor, float units){
    depth += (z_slope * factor + std::numeric_limits<float>::min() * units);
}

template<
    bool TEX_POWER_OF_TWO,
    bool NON_NEGATIVE_TEX_COORDS
>
void Rasterizer::drawPixel(const Rasterizer::PixelDrawInfo& info, int col, int row, unsigned& drawn_fragments) const{
    bool skip = false;

    // Calculate depth factor used in perspective correct interpolation
    float z_inter = 1.0f / glm::dot(info.vec_1_over_w, info.bary_coords);

    bool depth_pass = false;
    float depth;

    bool stencil_test = info.set->stencil_test, stencil_pass = false;
    StencCell* stencil_value = nullptr;

    if (stencil_test){
        stencil_value = &info.cur_stencil_row[col];
        stencil_pass = stencilTest(*stencil_value, info.set->stencil_ref, info.set->stencil_fun);
        if (!stencil_pass){
            stencilResolve(stencil_value, info.set->stencil_ref, info.set->stencil_fail_op);
            return;
        }
    }


    if (info.set->depth_test){
        depth = glm::dot(info.vec_depth, info.bary_coords);
        if (info.set->offset_enabled){
            addOffset(depth, info.z_slope, info.set->offset_options.factor, info.set->offset_options.units);
        }
        if (depthTest(info.cur_depth_row[col], depth, info.set->depth_func)){
            depth_pass = true;
        }
    }
    else{
        depth = info.cur_depth_row[col];
        if (info.set->offset_enabled){
            addOffset(depth, info.z_slope, info.set->offset_options.factor, info.set->offset_options.units);
        }
        depth_pass = true;
    }
    // Depth test passed or not required
    if (!depth_pass){
        if (info.set->stencil_test){
            stencilResolve(stencil_value, info.set->stencil_ref, info.set->stencil_dfail_op);
        }
    }
    else{
        if (info.set->stencil_test){
            stencilResolve(stencil_value, info.set->stencil_ref, info.set->stencil_pass_op);
        }
        ColorCell color;

        Vec2 int_tex_coords;
        // If texturing, sample the texture at interpolated coordinates
        if (info.set->tex){
            int_tex_coords = Vec2{
                glm::dot(info.tex_coords_x_z, info.bary_coords),
                glm::dot(info.tex_coords_y_z, info.bary_coords)
            };

            int_tex_coords.x *= z_inter;
            int_tex_coords.y *= z_inter;
            color = info.set->tex->sampleTex<TEX_POWER_OF_TWO, NON_NEGATIVE_TEX_COORDS>(int_tex_coords.x, int_tex_coords.y);
        }
        // Else sample color
        else{
            color = ColorCell{
                static_cast<unsigned char>(std::clamp(255 * (glm::dot(info.blue_vec, info.bary_coords)  * z_inter), 0.0f, 255.0f)),
                static_cast<unsigned char>(std::clamp(255 * (glm::dot(info.green_vec, info.bary_coords) * z_inter), 0.0f, 255.0f)),
                static_cast<unsigned char>(std::clamp(255 * (glm::dot(info.red_vec, info.bary_coords)   * z_inter), 0.0f, 255.0f)),
                static_cast<unsigned char>(std::clamp(255 * (glm::dot(info.alpha_vec, info.bary_coords) * z_inter), 0.0f, 255.0f))
            };
        }
        // Modulate texture color with raw color
        if (info.set->texture_env == GL_MODULATE){
            color = ColorCell{
                static_cast<unsigned char>(std::clamp(255 * (glm::dot(info.blue_vec, info.bary_coords)  * z_inter), 0.0f, 255.0f)),
                static_cast<unsigned char>(std::clamp(255 * (glm::dot(info.green_vec, info.bary_coords) * z_inter), 0.0f, 255.0f)),
                static_cast<unsigned char>(std::clamp(255 * (glm::dot(info.red_vec, info.bary_coords)   * z_inter), 0.0f, 255.0f)),
                static_cast<unsigned char>(std::clamp(255 * (glm::dot(info.alpha_vec, info.bary_coords) * z_inter), 0.0f, 255.0f))
            } * color;
        }

        if (info.set->fog_enabled){
            float eye_dist = glm::dot(info.vec_eye_distance, info.bary_coords);
            calcFog(info.set->fog_options, color, eye_dist);
        }
        // If depth buffer write is on, write it
        if (info.set->depth_mask){
            info.cur_depth_row[col] = depth;
        }

        // If blending is on, update the color based on the currently stored color
        if (info.set->blend){
            const ColorCell& dst = info.color_row[col];
            Vec4 src_fac = getBlendFactors(info.set->src_blend_func, color, dst);
            Vec4 dst_fac = getBlendFactors(info.set->dst_blend_func, color, dst);

            color.red   = std::min(static_cast<int>(ColorCell::MAX_VALUE), static_cast<int>(src_fac.x * color.red   +  dst_fac.x * dst.red));
            color.green = std::min(static_cast<int>(ColorCell::MAX_VALUE), static_cast<int>(src_fac.y * color.green +  dst_fac.y * dst.green));
            color.blue  = std::min(static_cast<int>(ColorCell::MAX_VALUE), static_cast<int>(src_fac.z * color.blue  +  dst_fac.z * dst.blue));
            color.alpha = std::min(static_cast<int>(ColorCell::MAX_VALUE), static_cast<int>(src_fac.w * color.alpha +  dst_fac.w * dst.alpha));
        }

        // If alpha test is on and it does not pass, skip writing color
        if (info.set->alpha_test){
            if (!alphaCheck(color, info.set->alpha_test_func, info.set->alpha_test_val)){
                skip = true;
            }
        }
        if (!skip){
            drawn_fragments++;

            if (info.set->color_mask & 0b1111){
                info.color_row[col] = color;
            }
            else{
                if (info.set->color_mask & 0b1000){
                    info.color_row[col].red = color.red;
                }
                if (info.set->color_mask & 0b0100){
                    info.color_row[col].green = color.green;
                }
                if (info.set->color_mask & 0b0010){
                    info.color_row[col].blue = color.blue;
                }
                if (info.set->color_mask & 0b0001){
                    info.color_row[col].alpha = color.alpha;
                }
            }
        }
    }
}


template<
    bool TEX_POWER_OF_TWO,
    bool NON_NEGATIVE_TEX_COORDS
>
unsigned Rasterizer::drawTriangleInternalHalfSpace(
    const DrawSettings settings,
    FrameBuffer& fb,
    Vertex& point_0,
    Vertex& point_1,
    Vertex& point_2
){
    if (fb.height == 0 || fb.width == 0) {
        return 0;
    }
    m_stats.handled_tris++;

    // Clear vertices buffer, emplace current triangle vertices
    m_clipped_vertices.clear();
    m_clipped_vertices.emplace_back(point_0);
    m_clipped_vertices.emplace_back(point_1);
    m_clipped_vertices.emplace_back(point_2);

    // Transform vertices
    if (!transformVertices(settings, fb.width, fb.height, m_clipped_vertices) || m_clipped_vertices.size() < 3){
        m_stats.discarded_tris++;
        return 0;
    }

    unsigned handled_fragments = 0, drawn_fragments = 0;

    PixelDrawInfo pixel_info;
    pixel_info.set = &settings;
    /**
     * We draw a triangle fan from clipped vertices
     * If no clipping is done, just one triangle is drawn
     */
    for (size_t i = 0; i < m_clipped_vertices.size() - 2; i++){

        Vertex& point_0 = m_clipped_vertices[0];
        Vertex& point_1 = m_clipped_vertices[i + 1];
        Vertex& point_2 = m_clipped_vertices[i + 2];

        pixel_info.z_slope = std::max<float>({
            (point_1.pos.z - point_0.pos.z) / (point_1.pos.x - point_0.pos.x),
            (point_1.pos.z - point_0.pos.z) / (point_1.pos.y - point_0.pos.y),
            (point_2.pos.z - point_0.pos.z) / (point_2.pos.x - point_0.pos.x),
            (point_2.pos.z - point_0.pos.z) / (point_2.pos.x - point_0.pos.x)
        });
        int min_y = std::clamp<int>(static_cast<int>(std::min({point_0.pos.y, point_1.pos.y, point_2.pos.y})), 0, fb.height - 1);
        int max_y = std::clamp<int>(static_cast<int>(std::max({point_0.pos.y, point_1.pos.y, point_2.pos.y})) + 1, 0, fb.height - 1);

        int min_x = std::clamp<int>(static_cast<int>(std::min({point_0.pos.x, point_1.pos.x, point_2.pos.x})), 0, fb.width - 1);
        int max_x = std::clamp<int>(static_cast<int>(std::max({point_0.pos.x, point_1.pos.x, point_2.pos.x})) + 1, 0, fb.width - 1);

        if (settings.scissor_test){
            min_x = std::clamp(min_x, settings.scissor_box.min_x, settings.scissor_box.max_x);
            min_y = std::clamp(min_y, settings.scissor_box.min_y, settings.scissor_box.max_y);
        }

        const auto edge_fun = [&](const Vec2& p_0, const Vec2& p_1, const Vec2& p_2) -> float {
            return (p_0.x - p_1.x)*(p_2.y - p_1.y) - (p_0.y - p_1.y)*(p_2.x - p_1.x);
        };

        Vec2 point_0_pos = Vec2{point_0.pos.x, point_0.pos.y};
        Vec2 point_1_pos = Vec2{point_1.pos.x, point_1.pos.y};
        Vec2 point_2_pos = Vec2{point_2.pos.x, point_2.pos.y};

        float tri_space = edge_fun(
            Vec2{point_2.pos.x, point_2.pos.y},
            Vec2{point_0.pos.x, point_0.pos.y},
            Vec2{point_1.pos.x, point_1.pos.y}
        );

        bool is_clockwise = tri_space > 0;

        char sign = is_clockwise ? 1 : -1;

        const auto f01_fun = [&](const Vec2& p) -> float {return sign * edge_fun(p, point_0_pos, point_1_pos);};
        const auto f12_fun = [&](const Vec2& p) -> float {return sign * edge_fun(p, point_1_pos, point_2_pos);};
        const auto f20_fun = [&](const Vec2& p) -> float {return sign * edge_fun(p, point_2_pos, point_0_pos);};

        // Taken from https://fgiesen.wordpress.com/2013/02/08/triangle-rasterization-in-practice/
        const auto isTopLeft = [&](const Vec2& p0, const Vec2& p1) -> bool {
            // Top
            if ((p0.y == p1.y) && (p1.x < p0.x)){
                return true;
            }
            // Left
            if (p0.y > p1.y){
                return true;
            }
            return false;
        };

        float c0_check = 0, c1_check = 0, c2_check = 0;
        if (sign > 0){
            c0_check = isTopLeft(point_1_pos, point_2_pos) ? std::numeric_limits<float>::denorm_min() : 0;
            c1_check = isTopLeft(point_2_pos, point_0_pos) ? std::numeric_limits<float>::denorm_min() : 0;
            c2_check = isTopLeft(point_0_pos, point_1_pos) ? std::numeric_limits<float>::denorm_min() : 0;
        }
        else{
            c0_check = isTopLeft(point_2_pos, point_1_pos) ? std::numeric_limits<float>::denorm_min() : 0;
            c1_check = isTopLeft(point_0_pos, point_2_pos) ? std::numeric_limits<float>::denorm_min() : 0;
            c2_check = isTopLeft(point_1_pos, point_0_pos) ? std::numeric_limits<float>::denorm_min() : 0;
        }

        float abc_fac = sign * (1.0f / tri_space);


        const float f01 = f01_fun(Vec2{min_x, min_y});
        const float f12 = f12_fun(Vec2{min_x, min_y});
        const float f20 = f20_fun(Vec2{min_x, min_y});

        float c0 = f12;
        float c0_row_start = c0;
        float c0_dx = f12_fun(Vec2{min_x + 1, min_y}) - c0;
        float c0_dy = f12_fun(Vec2{min_x, min_y + 1}) - c0;

        float c1 = f20;
        float c1_row_start = c1;
        float c1_dx = f20_fun(Vec2{min_x + 1, min_y}) - c1;
        float c1_dy = f20_fun(Vec2{min_x, min_y + 1}) - c1;

        float c2 = f01;
        float c2_row_start = c2;
        float c2_dx = f01_fun(Vec2{min_x + 1, min_y}) - c2;
        float c2_dy = f01_fun(Vec2{min_x, min_y + 1}) - c2;

        /**
         * @brief Vectors of vertex data for later interpolation by barycentric coordinates
         *
         * During transformVertices, the w component of pos is set to 1/w, thus we essentially
         * do [value]/w for each tracked value. This is necessary for perspective correction.
         *
         */
        pixel_info.red_vec = {
            point_0.color.x * point_0.pos.w,
            point_1.color.x * point_1.pos.w,
            point_2.color.x * point_2.pos.w
        };
        pixel_info.green_vec = {
            point_0.color.y * point_0.pos.w,
            point_1.color.y * point_1.pos.w,
            point_2.color.y * point_2.pos.w
        };
        pixel_info.blue_vec = {
            point_0.color.z * point_0.pos.w,
            point_1.color.z * point_1.pos.w,
            point_2.color.z * point_2.pos.w
        };
        pixel_info.alpha_vec = {
            point_0.color.w * point_0.pos.w,
            point_1.color.w * point_1.pos.w,
            point_2.color.w * point_2.pos.w
        };

        pixel_info.tex_coords_x_z = {
            point_0.tex_coord.x * point_0.pos.w,
            point_1.tex_coord.x * point_1.pos.w,
            point_2.tex_coord.x * point_2.pos.w
        };
        pixel_info.tex_coords_y_z = {
            point_0.tex_coord.y * point_0.pos.w,
            point_1.tex_coord.y * point_1.pos.w,
            point_2.tex_coord.y * point_2.pos.w
        };

        /**
         * @brief pos.w was already precalculated as 1/w, thus we just set the value
         */
        pixel_info.vec_1_over_w = {
            point_0.pos.w,
            point_1.pos.w,
            point_2.pos.w
        };

        pixel_info.vec_depth = {
            point_0.pos.z,
            point_1.pos.z,
            point_2.pos.z
        };

        pixel_info.vec_eye_distance = {
            point_0.eye_distance,
            point_1.eye_distance,
            point_2.eye_distance
        };
        ///

        int thread_num = 1;
        char* thread_cnt_var = std::getenv("CGL_THREADS");
        if (thread_cnt_var){
            try{
                thread_num = std::stoi(thread_cnt_var);
            }
            catch(...){

            }
        }
        bool init = false;
        /**
         * Iterate rows from bottom to top
         */
        #pragma omp parallel for schedule(static, 1) num_threads(thread_num) \
            firstprivate(init, c0, c1, c2, c0_row_start, c1_row_start, c2_row_start, pixel_info) \
            shared (fb, min_x, max_x, min_y, max_y, abc_fac, thread_num, c0_check, c1_check, c2_check, c0_dx, c0_dy, c1_dx, c1_dy, c2_dx, c2_dy) \
            reduction(+:handled_fragments) reduction(+:drawn_fragments) \
            default(none)
        for (int row = min_y; row <= max_y; row++){
            if (!init){
                c0_row_start += (c0_dy * omp_get_thread_num());
                c1_row_start += (c1_dy * omp_get_thread_num());
                c2_row_start += (c2_dy * omp_get_thread_num());
                init = true;
            }
            pixel_info.cur_depth_row = fb.depth_buffer.data() + (fb.width * (fb.height - 1 - row));
            pixel_info.cur_stencil_row = fb.stencil_buffer.data() + (fb.width * (fb.height - 1 - row));
            pixel_info.color_row = fb.color_buffer.data() + (fb.width * (fb.height - 1 - row));
            pixel_info.drawn_fragments = &drawn_fragments;


            c0 = c0_row_start;
            c1 = c1_row_start;
            c2 = c2_row_start;

            int from, to;
            calcRowRange(c0, c0_dx, c1, c1_dx, c2, c2_dx, from, to);

            from += min_x;
            to += from;

            from = std::clamp(from, min_x, max_x);
            to = std::clamp(to, min_x, max_x);

            c0 += c0_dx * (from - min_x);
            c1 += c1_dx * (from - min_x);
            c2 += c2_dx * (from - min_x);

            /**
             * Iterate over fragments on the row from left to right
             */
            for (int col = from; col <= to; col++ ){
                if (c0 >= c0_check && c1 >= c1_check && c2 >= c2_check){
                    handled_fragments++;
                    // Get barycentric coordinates of the current point

                    pixel_info.bary_coords.x = c0 * abc_fac;
                    pixel_info.bary_coords.y = c1 * abc_fac;
                    pixel_info.bary_coords.z = 1.0f - pixel_info.bary_coords.x - pixel_info.bary_coords.y;

                    drawPixel<TEX_POWER_OF_TWO, NON_NEGATIVE_TEX_COORDS>(pixel_info, col, row, drawn_fragments);
                }
                c0 += c0_dx;
                c1 += c1_dx;
                c2 += c2_dx;

            }
            c0_row_start += (c0_dy * thread_num);
            c1_row_start += (c1_dy * thread_num);
            c2_row_start += (c2_dy * thread_num);
        }

    }
    m_stats.handled_fragments += handled_fragments;
    m_stats.drawn_fragments += drawn_fragments;
    return handled_fragments;
}

unsigned Rasterizer::drawTriangle(
    DrawSettings settings,
    FrameBuffer& fb,
    Vertex& point_0,
    Vertex& point_1,
    Vertex& point_2
){
    m_triangle_draw_flags[0] = (settings.tex && settings.tex->isPowerOfTwo());


    m_triangle_draw_flags[1] = (
        point_0.tex_coord.x >= 0 && point_0.tex_coord.y >= 0 &&
        point_1.tex_coord.x >= 0 && point_1.tex_coord.y >= 0 &&
        point_2.tex_coord.x >= 0 && point_2.tex_coord.y >= 0
    );
    if (!m_triangle_draw_flags[1]){
        float min = std::floor(std::min({
            point_0.tex_coord.x, point_0.tex_coord.y,
            point_1.tex_coord.x, point_1.tex_coord.y,
            point_2.tex_coord.x, point_2.tex_coord.y
        }));
        min *= -1;
        point_0.tex_coord.x += min;
        point_0.tex_coord.y += min;
        point_1.tex_coord.x += min;
        point_1.tex_coord.y += min;
        point_2.tex_coord.x += min;
        point_2.tex_coord.y += min;

        m_triangle_draw_flags[1] = true;
    }

    return drawTriangleInternalChain<0>(settings, fb, point_0, point_1, point_2);
}


inline int calcXCoord(float slope, int y_coord, int x_base){
    return std::roundf(slope*y_coord + x_base);
}
// Bresenham's line algorithm
void Rasterizer::plotLine(unsigned width, unsigned height, IVec2 from, IVec2 to, bool marks_starting, bool cut_end){
    bool marks_ending = !marks_starting;

    // Make sure from y coord is lower than to coord
    if (from.y > to.y){
        plotLine(width, height, to, from, marks_starting, cut_end);
        return;
    }
    // Resize draw buffer if it's too small
    if (m_line_draw_buffer.size() < height){
        m_line_draw_buffer.resize(height);
    }

    int min_x = std::min(from.x, from.x);
    int max_x = std::max(from.x, from.x);

    // If delta of y coord is 0, just write the boundaries
    if (to.y == from.y){
        if (marks_starting)
            m_line_draw_buffer[to.y].left = min_x;
        if (marks_ending)
            m_line_draw_buffer[to.y].right = max_x;
        return;
    }

    /**
     * Plotting is done based on a linear function, where we calculate x values for each y row
     * x = slope * y + x_base
     */

    float slope = (static_cast<float>(to.x) - from.x) / (static_cast<float>(to.y) - from.y);
    int x_base = from.x;

    /**
     * Iterate over rows and calculate the X value for each one
     */
    for (int y = from.y; y <= to.y; y++){
        if (marks_starting)
            m_line_draw_buffer[y].left = calcXCoord(slope, (y - from.y), x_base);
        if (marks_ending){
            m_line_draw_buffer[y].right = calcXCoord(slope, (y - from.y), x_base) - (cut_end ? 1 : 0); // -1 to avoid overdraw of neighboring triangles

        }
    }
}

PointsOrdering Rasterizer::orderTriangleVerticesByX(const Vec3& point_0, const Vec3& point_1, const Vec3& point_2){
    return
        (point_0.x >= point_1.x) ? ((point_1.x >= point_2.x) ? PointsOrdering{0, 1, 2}   :
                                   ((point_0.x >= point_2.x) ? PointsOrdering{0, 2, 1}   :
                                                               PointsOrdering{2, 0, 1})) :
        (point_1.x >= point_2.x) ? ((point_0.x >= point_2.x) ? PointsOrdering{1, 0, 2}   :
                                                               PointsOrdering{1, 2, 0})  :
                                                               PointsOrdering{2, 1, 0};
}

PointsOrdering Rasterizer::orderTriangleVerticesByY(const Vec3& point_0, const Vec3& point_1, const Vec3& point_2){
    return
        (point_0.y >= point_1.y) ? ((point_1.y >= point_2.y) ? PointsOrdering{0, 1, 2}   :
                                   ((point_0.y >= point_2.y) ? PointsOrdering{0, 2, 1}   :
                                                               PointsOrdering{2, 0, 1})) :
        (point_1.y >= point_2.y) ? ((point_0.y >= point_2.y) ? PointsOrdering{1, 0, 2}   :
                                                               PointsOrdering{1, 2, 0})  :
                                                               PointsOrdering{2, 1, 0};
}

bool Rasterizer::clearBuffer(
    FrameBuffer& fb,
    GLclampf red,
    GLclampf green,
    GLclampf blue,
    GLclampf alpha,
    GLfloat clear_depth,
    StencCell stencil_clear,
    GLbitfield mask
){
    ColorCell clear_color = ColorCell{
        .blue =  static_cast<unsigned char>(std::clamp(static_cast<int>(blue  * ColorCell::MAX_VALUE), 0, static_cast<int>(ColorCell::MAX_VALUE))),
        .green = static_cast<unsigned char>(std::clamp(static_cast<int>(green * ColorCell::MAX_VALUE), 0, static_cast<int>(ColorCell::MAX_VALUE))),
        .red =   static_cast<unsigned char>(std::clamp(static_cast<int>(red   * ColorCell::MAX_VALUE), 0, static_cast<int>(ColorCell::MAX_VALUE))),
        .alpha = static_cast<unsigned char>(std::clamp(static_cast<int>(alpha * ColorCell::MAX_VALUE), 0, static_cast<int>(ColorCell::MAX_VALUE)))
    };
    if (mask & GL_COLOR_BUFFER_BIT){
        std::fill(fb.color_buffer.begin(), fb.color_buffer.end(), clear_color);
    }
    if (mask & GL_DEPTH_BUFFER_BIT){
        std::fill(fb.depth_buffer.begin(), fb.depth_buffer.end(), clear_depth);
    }
    if (mask & GL_STENCIL_BUFFER_BIT){
        std::fill(fb.stencil_buffer.begin(), fb.stencil_buffer.end(), stencil_clear);
    }

    return true;
}

} // namespace cgl
