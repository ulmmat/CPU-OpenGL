#pragma once


#include "dataStructures/vector.h"
#include "renderer/MatrixStacks.h"
#include "renderer/GenericBuffer.h"
#include "renderer/Rasterizer.h"
#include "renderer/Vertex.h"
#include "renderer/textures/Texture.h"

#include "ogl/ogl_constants.h"

#include "dataStructures/optional.h"

namespace cgl
{

enum class PrimitiveType : GLenum{
    GL_POINTS = 0x0000,
    GL_LINES = 0x0001,
    GL_LINE_LOOP = 0x0002,
    GL_LINE_STRIP = 0x0003,
    GL_TRIANGLES = 0x0004,
    GL_TRIANGLE_STRIP = 0x0005,
    GL_TRIANGLE_FAN = 0x0006,
    GL_QUADS = 0x0007,
    GL_QUAD_STRIP = 0x0008,
    GL_POLYGON = 0x0009
};

enum class PrimitiveVertexCount : GLenum{
    POINT,
    LINE,
    TRIANGLE,
    QUAD,
    POLYGON
};

/** Used to ensure automatic initialization in a map*/
struct InitBool{
    bool val = false;
};

struct BlendOptions{
    GLenum source_fun = GL_ONE;
    GLenum dest_fun = GL_ZERO;
};

/**
 * @brief Main class for handling OpenGL requests and storing state
 *
 * Somewhat of a god class, it handles matrix stacks, owns framebuffers,
 * handles all OpenGL requests and delegates drawing to a Rasterizer class instance
 */
class Renderer{
    public:

        /**
         * @brief Return draw stats from rasterizer and reset them
         */
        Rasterizer::DrawStats fetchFrameStats();
        /**
         * @brief Resize all framebuffers
         */
        void resizeFramebuffers(int width, int height);

        /**
         * @brief Set the id of the draw framebuffer
         *
         * Currently not working, as only one buffer is used
         */
        void setDrawFramebuffer(GLenum type);
        GLenum getReadFramebuffer() const;

        /**
         * @brief Set the id of the read framebuffer
         *
         * Currently not working, as only one buffer is used
         */
        void setReadFramebuffer(GLenum type);
        GLenum getDrawFramebuffer() const;


        /**
         * Returns the map of all framebuffer IDs mapped to the color buffer data
         */
        Map<GLenum, FrameBuffer*> getFramebuffers();


        /** Set which faces will be culled in backface culling */
        void setBackfaceCullMode(GLenum mode);
        /** Turn backface culling on/off */
        void useBackfaceCull(bool val);

        /** Get the value of any property from set capability (~glIsEnabled()) */
        bool getCapability(GLenum capability) const;
        /** Set value of a property (~glEnable, ~glDisable) */
        void setCapability(GLenum capability, bool value);

        /** Set some OpenGL 1.1 properties (~glEnableClientState, ~glDisableClientState) */
        void setClientState(GLenum state, bool value);
        bool getClientState(GLenum state);

        /** Set functions for calculating source and destination factors when blending */
        void setBlending(GLenum sfactor, GLenum dfactor);

        /**
         * Set function and reference value
         *
         * Possible functions:
         *      GL_NEVER
         *      GL_LESS
         *      GL_EQUAL
         *      GL_LEQUAL
         *      GL_GREATER
         *      GL_NOTEQUAL
         *      GL_GEQUAL
         *      GL_ALWAYS
         */
        void setAlphaFunc(GLenum func, GLclampf val);

        void setDepthFunc(GLenum func);
        void setDepthMask(GLboolean flag);
        void setDepthRange(GLfloat near, GLfloat far);

        /**
         * Color used when clearing the framebuffer
         */
        void setClearColor(Vec4 color);
        void clear();

        /**
         * @brief Set color used for drawing operations
         */
        void setMainColor(Vec4 color);




        /** Matrix Operations */

        /**
         * @brief Set the current matrix stack (= current matrix)
         *
         * Possible options:
         *      GL_MODELVIEW
         *      GL_PROJECTION
         *
         * Currently GL_TEXTURE and GL_COLOR are unimplemented
         */
        void setMatrixStack(GLenum stack);

        /**
         * @brief Directly set the matrix on the top of the current stack
         */
        void setCurMatrix(const Mat4& mat);

        /**
         * @brief Pop matrix from current stack
         *
         * As per OpenGL standard, pop should not be called on stacks with 1 matrix
         */
        void popMatrix();
        /**
         * @brief Push matrix on top of the current stack
         *
         * The new matrix is copied over from the current matrix
         */
        void pushMatrix();

        const Mat4& curMatrix() const;

        void rotateMat(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
        void rotateMatd(GLfloat angle, GLdouble x, GLdouble y, GLdouble z);

        void translateMat(GLfloat x, GLfloat y, GLfloat z);
        void translateMatd(GLdouble x, GLdouble y, GLdouble z);

        void perspectiveMat(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

        void frustumMat(GLdouble left, GLdouble right,
                        GLdouble bottom, GLdouble top,
                        GLdouble near_val, GLdouble far_val);
        void orthoMat(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val);

        enum class BufferType{
            VERTEX,
            COLOR,
            NORMAL,
            TEX_COORD,
            EDGE
        };

        /** Vertex Buffers */

        /**
         * @brief Set a data buffer of category type
         */
        void setGenericBuffer(BufferType type, const GenericBuffer& buf);

        template<typename TIndices>
        void drawElements(GLenum mode, GLsizei count, GLenum type, const TIndices* indices);

        void drawArrays(GLenum mode, GLint first, GLsizei count);

        const MatrixStacks& getMatrixStack() const;


        /** Draw Transaction */
        void beginDraw(PrimitiveType type);

        void addVertex(const Vec3& vec);
        void setVertexNormal(const Vec3& norm);
        void setVertexColor(const Vec4& color);
        void setVertexTexCoords(const Vec2& coords);
        void endDraw();

        template<typename TIndices>
        void drawTrianglesInternal(DrawSettings& set, FrameBuffer& fb, GenericBuffer vertex_data, const TIndices* indices, GLint count, GenericBuffer tex_buf, GenericBuffer color_buf, Texture* tex){
            m_rasterizer.drawTriangles<TIndices>(set, fb, vertex_data, indices, count, tex_buf, color_buf, getCapability(GL_TEXTURE_2D) ? tex : nullptr);
        }


        /** Textures */
        void generateTextures(GLsizei n, GLuint* textures);
        void bindTexture(GLuint texture);
        void deleteTextures(GLsizei n, const GLuint* textures);
        void setTextureParameter(GLenum target, GLenum pname, GLint param);

        void setTexture(
            GLenum target, GLint level,
            GLint internal_format,
            GLsizei width, GLsizei height,
            GLint border, GLenum format, GLenum type,
            const GLvoid* pixels
        );

        void subTexture(GLenum target,GLint level,
            GLint xoffset,GLint yoffset,
            GLsizei width,GLsizei height,
            GLenum format,GLenum type,
            const GLvoid* pixels
        );
        void setTextureEnv(GLenum mode);

        DrawSettings createDrawSettings() const;

    private:


        Mat4& curMatrix();
        FrameBuffer& drawFramebuffer();
        FrameBuffer& readFramebuffer();

        void transactionDoDraw();

        void drawTriangleInternal(
            FrameBuffer& fb,
            Vertex point_0,
            Vertex point_1,
            Vertex point_2
        );

        // Vector<char> fb;

        Vector<GLuint> m_array_index;

        mutable Map<GLenum, InitBool> m_capabilities;
        mutable Map<GLenum, InitBool> m_client_state;
        BlendOptions m_blend_options;

        MatrixStacks m_mat_stacks;
        MatStack* m_cur_stack = &m_mat_stacks.modelview_stack;
        bool m_matrices_modified = true;

        Vec4 m_clear_color;
        Vec4 m_cur_color;

        Vector<GLuint> m_indices_buffer;
        GLenum m_cull_mode;
        bool m_backface_cull;

        /**
         * Rasterizer instance to handle the main drawing
         */
        Rasterizer m_rasterizer;


        // Buffers

        GenericBuffer vertex_pointer;
        GenericBuffer color_pointer;
        GenericBuffer normal_pointer;
        GenericBuffer tex_coord_pointer;
        GenericBuffer edge_pointer;
        GenericBuffer dummy_buffer;

        /**
         * @brief All settable generic buffers
         */
        const Map<BufferType, GenericBuffer*> BUFFER_MAP = {
            {BufferType::VERTEX, &vertex_pointer},
            {BufferType::COLOR,  &color_pointer},
            {BufferType::NORMAL,  &normal_pointer},
            {BufferType::TEX_COORD,  &tex_coord_pointer},
            {BufferType::EDGE,  &edge_pointer}
        };


        Map<GLenum, FrameBuffer> m_framebuffers = {
            {GL_FRONT, FrameBuffer{}},
            {GL_BACK, FrameBuffer{}}
        };


        GLenum m_draw_framebuffer = GL_FRONT;
        GLenum m_read_framebuffer = GL_FRONT;

        /** Transactions */
        Opt<PrimitiveType> m_begin_transaction = NULLOPT;

        PrimitiveVertexCount m_tr_vertex_cnt;

        /**
         * @brief Info about vertices in a begin/end transaction
         *
         * The last vertex is not valid, and is used to modify the passed normal/tex/color info,
         * before the vertex position itself is passed;
         */
        Vector<Vertex> m_vertices_for_draw;

        // Alpha
        GLenum m_alpha_func = GL_ALWAYS;
        GLclampf m_alpha_val = 0.0f;

        // Depth

        GLenum m_depth_func = GL_LESS;
        GLboolean m_depth_mask = false;
        GLfloat m_depth_range_near = 0.0f;
        GLfloat m_depth_range_far = 1.0f;

        // Textures

        /** All created textures */
        Map<GLuint, Texture> m_textures;

        /** Currently bound texture */
        Texture* m_cur_texture = nullptr;
        /** ID of currently bound texture */
        GLuint m_cur_texture_id = 0;
        /** Counter used when assigning IDs to created textures */
        size_t m_tex_ctr = 0;
        GLenum m_texture_env = GL_REPLACE;




};


} // namespace cgl
