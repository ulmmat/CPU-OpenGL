#pragma once

#include "dataStructures/array.h"
#include "utility/print.h"
#include "renderer/framebuffer/FrameBuffer.h"
#include "renderer/Vertex.h"
#include "renderer/textures/Texture.h"
#include "renderer/GenericBuffer.h"

#include <glm/gtx/string_cast.hpp>

namespace cgl
{

/**
 * Used when ordering triangle vertices,
 * marks index of the vertices in the specified order
 */
struct PointsOrdering{
    char high;
    char mid;
    char low;
};

/**
 * @brief Options that alter the drawing process
 */
struct DrawSettings{
    bool cull_face = true; // Whether face culling is enabled
    GLenum cull_mode = GL_BACK; // Which side of faces to cull
    bool cull_ccw = true; // If true, cull counter clockwise faces. If false, cull clockwise faces.
    bool triangle_strip = false; // True if the currently drawn triangles form a strip.
                                 // Mainly used for handling culling.


    bool depth_test = true; // Whether depth testing is enabled
    GLenum depth_func = GL_LESS; // Function for depth testing
    bool depth_mask = true; // Whether writing to depth buffer is enabled

    /**
     * This is equal to [ (depth_range_far - depth_range_near) / 2) ], for easier calculation during the transformation
     * For the standard range of 0.0 - 1.0, this is set to [ (1.0 - 0.0) / 2 ] = 0.5
     */
    GLfloat depth_range_dif = 0.5;

    bool blend; // Whether blending is enabled
    GLenum src_blend_func = GL_ONE; // Blending function for calculation factors of the stored color
    GLenum dst_blend_func = GL_ONE; // Blending function for calculation factors of the stored color
    GLenum texture_env = GL_REPLACE; // How the texture is applied

    bool alpha_test = false; // Enable alpha testing (discarding fragments based on alpha channel)
    GLenum alpha_test_func = GL_ALWAYS; // Function for alpha testing
    GLclampf alpha_test_val = 0.0f; // Reference value for alpha testing

    Vec4 main_color; // Color used during drawing
};

/**
 * Horizontal boundaries for a line when plotting geometry
 */
struct PlottedRow{
    int left = 0;
    int right = 0;
};

/**
 * @brief Class for the main drawing operations
 *
 * This does does not own the framebuffer, which is passed to each draw function
 */
class Rasterizer{
    public:
        struct DrawStats{
            size_t handled_fragments = 0;
            size_t handled_tris = 0;
            size_t discarded_tris = 0;
            size_t drawn_fragments = 0;
        };


        const DrawStats& getStats() const;
        void resetStats();


        /**
         * @brief Set modelview and projection matrices for subsequent draw functions
         *
         * Custom method mainly for potential precalculations
         */
        void setMatrices(const Mat4& modelview, const Mat4& projection);

        /**
         * @brief Draw multiple triangles
         *
         * @tparam TIndices, integer type of the indices pointer.
         *
         * @param settings draw altering options
         * @param fb framebuffer to draw to
         * @param vertex_data vertex data pointer
         * @param indices indices from which elements are selected
         * @param count number of elements selected from indices (3 ~ 1 triangle)
         * @param tex_buf buffer with texture coordinates
         * @param color_buf buffer with color coordinates
         * @param tex optional texture for texturing
         */
        template<typename TIndices>
        void drawTriangles(DrawSettings settings, FrameBuffer& fb, GenericBuffer vertex_data, const TIndices* indices, GLint count, GenericBuffer tex_buf, GenericBuffer color_buf, Texture* tex){
            GLint tri_ctr = 0;
            for (GLint i = 0; i < count; i+=3){
                Vertex v0;
                Vertex v1;
                Vertex v2;

                TIndices index_0 = indices[i    ];
                TIndices index_1 = indices[i + 1];
                TIndices index_2 = indices[i + 2];
                if (vertex_data.size == 2){
                    v0.pos = Vec4(vertex_data.castElement<GLfloat>(index_0, 0), vertex_data.castElement<GLfloat>(index_0, 1), 0.0f, 1.0f);
                    v1.pos = Vec4(vertex_data.castElement<GLfloat>(index_1, 0), vertex_data.castElement<GLfloat>(index_1, 1), 0.0f, 1.0f);
                    v2.pos = Vec4(vertex_data.castElement<GLfloat>(index_2, 0), vertex_data.castElement<GLfloat>(index_2, 1), 0.0f, 1.0f);
                }
                else if (vertex_data.size == 3){
                    v0.pos = Vec4(vertex_data.castElement<GLfloat>(index_0, 0), vertex_data.castElement<GLfloat>(index_0, 1), vertex_data.castElement<GLfloat>(index_0, 2), 1.0f);
                    v1.pos = Vec4(vertex_data.castElement<GLfloat>(index_1, 0), vertex_data.castElement<GLfloat>(index_1, 1), vertex_data.castElement<GLfloat>(index_1, 2), 1.0f);
                    v2.pos = Vec4(vertex_data.castElement<GLfloat>(index_2, 0), vertex_data.castElement<GLfloat>(index_2, 1), vertex_data.castElement<GLfloat>(index_2, 2), 1.0f);
                }

                if (color_buf.ptr){
                    v0.color = Vec4(color_buf.castElement<GLfloat>(index_0, 0), color_buf.castElement<GLfloat>(index_0, 1), color_buf.castElement<GLfloat>(index_0, 2), 1.0f);
                    v1.color = Vec4(color_buf.castElement<GLfloat>(index_1, 0), color_buf.castElement<GLfloat>(index_1, 1), color_buf.castElement<GLfloat>(index_1, 2), 1.0f);
                    v2.color = Vec4(color_buf.castElement<GLfloat>(index_2, 0), color_buf.castElement<GLfloat>(index_2, 1), color_buf.castElement<GLfloat>(index_2, 2), 1.0f);
                }
                else{
                    v0.color = settings.main_color;
                    v1.color = settings.main_color;
                    v2.color = settings.main_color;
                }

                if (tex_buf.ptr){
                    v0.tex_coord = Vec2(tex_buf.castElement<GLfloat>(index_0, 0), tex_buf.castElement<GLfloat>(index_0, 1));
                    v1.tex_coord = Vec2(tex_buf.castElement<GLfloat>(index_1, 0), tex_buf.castElement<GLfloat>(index_1, 1));
                    v2.tex_coord = Vec2(tex_buf.castElement<GLfloat>(index_2, 0), tex_buf.castElement<GLfloat>(index_2, 1));
                }


                /**
                 * If we have a triangle strip, the cull direction must be swapped after each triangle
                 * to ensure proper orientation
                 */
                if (settings.triangle_strip && (tri_ctr % 2)){
                    settings.cull_ccw = !settings.cull_ccw;
                    drawTriangle(settings, fb, v0, v1, v2, tex);
                    settings.cull_ccw = !settings.cull_ccw;
                }
                else{
                    drawTriangle(settings, fb, v0, v1, v2, tex);
                }
                tri_ctr++;
            }
        }


        bool clearBuffer(FrameBuffer& fb, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

        unsigned drawTriangle(
            DrawSettings settings,
            FrameBuffer& fb,
            Vertex& point_0,
            Vertex& point_1,
            Vertex& point_2,
            Texture* tex = nullptr
        );

    private:

        /**
         * Transform vertices from the passed vector from local coordinates to
         * window coordinates
         *
         * The vector must be passed with 3 vertices of a triangle
         *
         * More vertices may be inserted if the triangle is to be clipped.
         * The Vertices are inserted in such a way that the output vertices
         * may be drawn as a triangle fan.
         *
         * @param width of the framebuffer
         * @param height of the framebuffer
         *
         * @return true proceed with drawing of the triangle
         * @return false if the triangle is to be discarded
         */
        bool transformVertices(const DrawSettings& settings, unsigned width, unsigned height, Vector<Vertex>& vertices);

        PointsOrdering orderTriangleVerticesByX(const Vec3& point_0, const Vec3& point_1, const Vec3& point_2);
        PointsOrdering orderTriangleVerticesByY(const Vec3& point_0, const Vec3& point_1, const Vec3& point_2);

        /**
         * @brief Buffer for plotting lines when drawing a single triangle
         *
         * Size must be at least as large as the framebuffer height.
         *
         * Each element corresponds to a row, with the left and right values specifying leftmost and rightmost
         * fragments to be drawn on that row
         *
         * This buffer is reset after each triangle.
         *
         */
        Vector<PlottedRow> m_line_draw_buffer;

        /** Used to store vertices after creating */
        Vector<Vertex> m_clipped_vertices;

        void plotLine(unsigned width, unsigned height, IVec2 from, IVec2 to, bool marks_starting, bool cut_end = true);

        Mat4 m_view_projection_matrix = Mat4{1.0f};

        DrawStats m_stats;


};

} // namespace cgl
