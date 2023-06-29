#include "renderer/Rasterizer.h"
#include "renderer/geometry/Line.h"
#include "renderer/geometry/Triangle.h"
#include "utility/print.h"
#include <glm/gtc/matrix_access.hpp>

#include <fstream>
#include <cmath>
#include <tuple>
#include <utility>
#include <algorithm>

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
        v.pos = m_view_projection_matrix * v.pos;
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
        Vec4 out = Vec4(((v.pos.x * one_over_w) * width  + width) * 0.5f,
                        ((v.pos.y * one_over_w) * height + height) * 0.5f,
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
unsigned Rasterizer::drawTriangle(
    DrawSettings settings,
    FrameBuffer& fb,
    Vertex& point_0,
    Vertex& point_1,
    Vertex& point_2,
    Texture* tex
){
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

    unsigned drawn_pixels = 0;

    /**
     * We draw a triangle fan from clipped vertices
     * If no clipping is done, just one triangle is drawn
     */
    for (size_t i = 0; i < m_clipped_vertices.size() - 2; i++){
        Vertex& point_0 = m_clipped_vertices[0];
        Vertex& point_1 = m_clipped_vertices[i + 1];
        Vertex& point_2 = m_clipped_vertices[i + 2];




        // Don't draw if the triangle is miniscule
        if (isDegenerateTriangle(point_0.pos, point_1.pos, point_2.pos))
            continue;

        Array<Vertex*, 3> vertices{&point_0, &point_1, &point_2};
        PointsOrdering points_y_ordering = orderTriangleVerticesByY(point_0.pos, point_1.pos, point_2.pos);
        char y_lo_index = points_y_ordering.low;
        char y_mi_index = points_y_ordering.mid;
        char y_hi_index = points_y_ordering.high;

        const Vec3& lowest_point  = vertices[points_y_ordering.low]->pos;
        const Vec3& middle_point  = vertices[points_y_ordering.mid]->pos;
        const Vec3& highest_point = vertices[points_y_ordering.high]->pos;

        /**
         * @brief Vectors of vertex data for later interpolation by barycentric coordinates
         *
         * During transformVertices, the w component of pos is set to 1/w, thus we essentially
         * do [value]/w for each tracked value. This is necessary for perspective correction.
         *
         */
        Vec3 red_vec = {
            vertices[y_lo_index]->color.x * vertices[y_lo_index]->pos.w,
            vertices[y_mi_index]->color.x * vertices[y_mi_index]->pos.w,
            vertices[y_hi_index]->color.x * vertices[y_hi_index]->pos.w
        };
        Vec3 green_vec = {
            vertices[y_lo_index]->color.y * vertices[y_lo_index]->pos.w,
            vertices[y_mi_index]->color.y * vertices[y_mi_index]->pos.w,
            vertices[y_hi_index]->color.y * vertices[y_hi_index]->pos.w
        };
        Vec3 blue_vec = {
            vertices[y_lo_index]->color.z * vertices[y_lo_index]->pos.w,
            vertices[y_mi_index]->color.z * vertices[y_mi_index]->pos.w,
            vertices[y_hi_index]->color.z * vertices[y_hi_index]->pos.w
        };
        Vec3 alpha_vec = {
            vertices[y_lo_index]->color.w * vertices[y_lo_index]->pos.w,
            vertices[y_mi_index]->color.w * vertices[y_mi_index]->pos.w,
            vertices[y_hi_index]->color.w * vertices[y_hi_index]->pos.w
        };

        Vec3 tex_coords_x_z = {
            vertices[y_lo_index]->tex_coord.x * vertices[y_lo_index]->pos.w,
            vertices[y_mi_index]->tex_coord.x * vertices[y_mi_index]->pos.w,
            vertices[y_hi_index]->tex_coord.x * vertices[y_hi_index]->pos.w
        };
        Vec3 tex_coords_y_z = {
            vertices[y_lo_index]->tex_coord.y * vertices[y_lo_index]->pos.w,
            vertices[y_mi_index]->tex_coord.y * vertices[y_mi_index]->pos.w,
            vertices[y_hi_index]->tex_coord.y * vertices[y_hi_index]->pos.w
        };

        /**
         * @brief pos.w was already precalculated as 1/w, thus we just set the value
         */
        Vec3 vec_1_over_w = {
            vertices[y_lo_index]->pos.w,
            vertices[y_mi_index]->pos.w,
            vertices[y_hi_index]->pos.w
        };

        Vec3 vec_depth = {
            vertices[y_lo_index]->pos.z,
            vertices[y_mi_index]->pos.z,
            vertices[y_hi_index]->pos.z
        };
        ///

        int y_indices[3];

        y_indices[0] = std::roundf(highest_point.y);
        y_indices[0] = std::clamp(y_indices[0], 0, static_cast<int>(fb.height - 1));

        y_indices[2] = std::roundf(lowest_point.y);
        if (y_indices[2] > y_indices[0])
            continue;
         y_indices[2] = std::clamp(y_indices[2], 0, y_indices[0]);

        y_indices[1] = std::roundf(middle_point.y);
        y_indices[1] = std::clamp(y_indices[1], y_indices[2], y_indices[0]);

        Line tallest_line = Line(lowest_point, highest_point);

        std::array<int, 3> x_indices;
        x_indices[2] = std::clamp<int>(std::roundf(lowest_point.x), 0, fb.width);
        x_indices[1] = std::clamp<int>(std::roundf(middle_point.x), 0, fb.width);
        x_indices[0] = std::clamp<int>(std::roundf(highest_point.x), 0, fb.width);

        /** Clear the draw buffer before plotting lines */
        std::fill(m_line_draw_buffer.begin(), m_line_draw_buffer.end(), PlottedRow{});

        /**
         * @brief The plotting is different whether the triangle hypotenuse is on the left or right of the
         * "middle" point
         */

        // Hypotenuse on the left
        if (tallest_line.isOnTheRight(middle_point)){
            plotLine(fb.width, fb.height, IVec2(x_indices[2], y_indices[2]), IVec2(x_indices[0], y_indices[0]), true);
            plotLine(fb.width, fb.height, IVec2(x_indices[2], y_indices[2]), IVec2(x_indices[1], y_indices[1]), false);
            plotLine(fb.width, fb.height, IVec2(x_indices[1], y_indices[1]), IVec2(x_indices[0], y_indices[0]), false);
        }
        // Hypotenuse on the right
        else{
            plotLine(fb.width, fb.height, IVec2(x_indices[2], y_indices[2]), IVec2(x_indices[0], y_indices[0]), false);
            plotLine(fb.width, fb.height, IVec2(x_indices[2], y_indices[2]), IVec2(x_indices[1], y_indices[1]), true);
            plotLine(fb.width, fb.height, IVec2(x_indices[1], y_indices[1]), IVec2(x_indices[0], y_indices[0]), true);

        }

        // For calculating barycentric coordinates
        Triangle2D tri = Triangle2D(
            glm::vec2(x_indices[2], y_indices[2]),
            glm::vec2(x_indices[1], y_indices[1]),
            glm::vec2(x_indices[0], y_indices[0])
        );

        y_indices[2] = std::clamp(y_indices[2], 0, static_cast<int>(m_line_draw_buffer.size() - 1));
        y_indices[0] = std::clamp(y_indices[0], 0, static_cast<int>(m_line_draw_buffer.size() - 1));

        int row;
        int col;
        Vec3 bary_coords;

        /**
         * @brief Iterate rows from bottom to top
         *
         * Don't draw the bottom most line to avoid overdraw with neighbouring triangles
         */
        for (row = y_indices[2] + 1; row <= y_indices[0]; row++){

            float* cur_row = fb.depth_buffer.data() + (fb.width * (fb.height - 1 - row));
            ColorCell* color_row = fb.color_buffer.data() + (fb.width * (fb.height - 1 - row));
            int row_right = m_line_draw_buffer[row].right;
            int row_left  = m_line_draw_buffer[row].left;

            #ifdef DEBUG
            if (row_right < 0 || row_right >= fb.width || row_left < 0){
                throw std::runtime_error("Should not happen, triangle should be properly clipped");
            }
            #endif

            /**
             * Iterate over fragments on the row from left to right
             */
            for (col = row_left; col <= row_right; col++ ){
                drawn_pixels++;
                // Get barycentric coordinates of the current point
                tri.getBarycentricCoordinates(
                    Vec2(col, row),
                    bary_coords
                );

                // Calculate depth factor used in perspective correct interpolation
                float z_inter = 1.0f / glm::dot(vec_1_over_w, bary_coords);

                bool depth_pass = false;
                float depth;


                if (settings.depth_test){
                    depth = glm::dot(vec_depth, bary_coords);
                    if (depthTest(cur_row[col], depth, settings.depth_func)){
                        depth_pass = true;
                    }
                }
                else{
                    depth = cur_row[col];
                    depth_pass = true;
                }
                // Depth test passed or not required
                if (depth_pass){
                    ColorCell color;

                    Vec2 int_tex_coords;
                    // If texturing, sample the texture at interpolated coordinates
                    if (tex){
                        int_tex_coords = Vec2{
                            glm::dot(tex_coords_x_z, bary_coords),
                            glm::dot(tex_coords_y_z, bary_coords)
                        };

                        int_tex_coords.x *= z_inter;
                        int_tex_coords.y *= z_inter;
                        color = tex->sampleTex(int_tex_coords.x, int_tex_coords.y);
                    }
                    // Else sample color
                    else{
                        color = ColorCell{
                            static_cast<unsigned char>(std::clamp(255 * (glm::dot(blue_vec, bary_coords)  * z_inter), 0.0f, 255.0f)),
                            static_cast<unsigned char>(std::clamp(255 * (glm::dot(green_vec, bary_coords) * z_inter), 0.0f, 255.0f)),
                            static_cast<unsigned char>(std::clamp(255 * (glm::dot(red_vec, bary_coords)   * z_inter), 0.0f, 255.0f)),
                            static_cast<unsigned char>(std::clamp(255 * (glm::dot(alpha_vec, bary_coords) * z_inter), 0.0f, 255.0f))
                        };
                    }
                    // Modulate texture color with raw color
                    if (settings.texture_env == GL_MODULATE){
                        color = ColorCell{
                            static_cast<unsigned char>(std::clamp(255 * (glm::dot(blue_vec, bary_coords)  * z_inter), 0.0f, 255.0f)),
                            static_cast<unsigned char>(std::clamp(255 * (glm::dot(green_vec, bary_coords) * z_inter), 0.0f, 255.0f)),
                            static_cast<unsigned char>(std::clamp(255 * (glm::dot(red_vec, bary_coords)   * z_inter), 0.0f, 255.0f)),
                            static_cast<unsigned char>(std::clamp(255 * (glm::dot(alpha_vec, bary_coords) * z_inter), 0.0f, 255.0f))
                        } * color;
                    }
                    // If depth buffer write is on, write it
                    if (settings.depth_mask){
                        cur_row[col] = depth;
                    }

                    // If blending is on, update the color based on the currently stored color
                    if (settings.blend){
                        const ColorCell& dst = color_row[col];
                        Vec4 src_fac = getBlendFactors(settings.src_blend_func, color, dst);
                        Vec4 dst_fac = getBlendFactors(settings.dst_blend_func, color, dst);

                        color.red   = std::min(static_cast<int>(ColorCell::MAX_VALUE), static_cast<int>(src_fac.x * color.red   +  dst_fac.x * dst.red));
                        color.green = std::min(static_cast<int>(ColorCell::MAX_VALUE), static_cast<int>(src_fac.y * color.green +  dst_fac.y * dst.green));
                        color.blue  = std::min(static_cast<int>(ColorCell::MAX_VALUE), static_cast<int>(src_fac.z * color.blue  +  dst_fac.z * dst.blue));
                        color.alpha = std::min(static_cast<int>(ColorCell::MAX_VALUE), static_cast<int>(src_fac.w * color.alpha +  dst_fac.w * dst.alpha));
                    }

                    // If alpha test is on and it does not pass, skip writing color
                    if (settings.alpha_test && !alphaCheck(color, settings.alpha_test_func, settings.alpha_test_val)){
                        continue;
                    }
                    else{
                        m_stats.drawn_fragments++;
                        color_row[col] = color;
                    }
                }
            }
        }
    }
    m_stats.handled_fragments += drawn_pixels;
    return drawn_pixels;
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

bool Rasterizer::clearBuffer(FrameBuffer& fb, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha){
    ColorCell clear_color = ColorCell{
        .blue =  static_cast<unsigned char>(std::clamp(static_cast<int>(blue),  0, static_cast<int>(ColorCell::MAX_VALUE))),
        .green = static_cast<unsigned char>(std::clamp(static_cast<int>(green), 0, static_cast<int>(ColorCell::MAX_VALUE))),
        .red =   static_cast<unsigned char>(std::clamp(static_cast<int>(red),   0, static_cast<int>(ColorCell::MAX_VALUE))),
        .alpha = static_cast<unsigned char>(std::clamp(static_cast<int>(alpha), 0, static_cast<int>(ColorCell::MAX_VALUE)))
    };
    std::fill(fb.depth_buffer.begin(), fb.depth_buffer.end(), 1.0f);
    std::fill(fb.color_buffer.begin(), fb.color_buffer.end(), clear_color);

    return true;
}

} // namespace cgl
