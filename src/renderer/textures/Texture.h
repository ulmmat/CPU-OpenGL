#pragma once

#include "ogl/ogl.h"
#include "ogl/ogl_constants.h"

#include "dataStructures/vector.h"
#include "renderer/framebuffer/FrameBuffer.h"

namespace cgl
{

/**
 * @brief Representation of color textures
 *
 * Mipmapping is currently not supported
 */
struct Texture{

    public:
        /**
         * Set texture data
         *
         * Level is ignored as mipmapping is unsupported
         *
         * Only 1 byte char / uchar pointer in an RGB / RGBA format
         * are supported
         */
        void setData(
            GLenum target, GLint level,
            GLint internalFormat,
            GLsizei width, GLsizei height,
            GLint border, GLenum format, GLenum type,
            const GLvoid* pixels
        );

        void setSubData(
            GLenum target,GLint level,
            GLint xoffset,GLint yoffset,
            GLsizei width,GLsizei height,
            GLenum format,GLenum type,
            const GLvoid* pixels
        );

        /**
         * @brief Get color directly from integer x and y coords
         */
        inline ColorCell queryByCoords(GLint w, GLint h){
            return m_data[((h % m_texture_height) * m_texture_width) + (w % m_texture_width)];
        }
        /**
         * Query a color using standard float x and y coords from interval [0; 1]
         *
         * Coordinates are expected to be non-negative
         */
        inline ColorCell sampleTex(float s_coord, float t_coord){

            // We only check the min filter

            // Nearest neighbour
            if (min_filter == GL_NEAREST){
                GLuint w = ((m_texture_width) * s_coord) + 0.5;
                GLuint h = ((m_texture_height) * t_coord) + 0.5;
                return m_data[((h % m_texture_height) * m_texture_width) + (w % m_texture_width)];
            }
            // Bilinear interpolation


            float w_f =( (m_texture_width) * s_coord) - 0.5;
            int w_0 = std::floor(w_f);
            int w_1 = w_0 + 1;
            float dif = std::abs(w_f - w_0);

            float h_f =( (m_texture_height) * t_coord) - 0.5;
            int h_0 = std::floor(h_f);
            int h_1 = h_0 + 1;
            float dif_h = std::abs(h_f - h_0);

            ColorCell c_00 = queryByCoords(w_0, h_0);
            ColorCell c_01 = queryByCoords(w_1, h_0);

            ColorCell c_10 = queryByCoords(w_0, h_1);
            ColorCell c_11 = queryByCoords(w_1, h_1);

            ColorCell ret{
                static_cast<unsigned char>((((c_00.blue  * (1.0-dif)) + (c_01.blue  * dif)) * (1.0-dif_h)) + (((c_10.blue  * (1.0-dif)) + (c_11.blue  * dif)) * dif_h)),
                static_cast<unsigned char>((((c_00.green * (1.0-dif)) + (c_01.green * dif)) * (1.0-dif_h)) + (((c_10.green * (1.0-dif)) + (c_11.green * dif)) * dif_h)),
                static_cast<unsigned char>((((c_00.red   * (1.0-dif)) + (c_01.red   * dif)) * (1.0-dif_h)) + (((c_10.red   * (1.0-dif)) + (c_11.red   * dif)) * dif_h)),
                static_cast<unsigned char>((((c_00.alpha * (1.0-dif)) + (c_01.alpha * dif)) * (1.0-dif_h)) + (((c_10.alpha * (1.0-dif)) + (c_11.alpha * dif)) * dif_h))
            };

            return ret;
        }

        GLenum min_filter = GL_NEAREST;
        GLenum mag_filter = GL_NEAREST;
        GLenum wrap_s = GL_REPEAT;
        GLenum wrap_t = GL_REPEAT;
        GLint level = 0;

    private:

        inline ColorCell* getRow(size_t row){
            return (m_data.data() + (row * m_texture_width));
        }

        Vector<ColorCell> m_data;
        GLuint m_texture_width;
        GLuint m_texture_height;





};

} // namespace cgl
