#pragma once

#include "ogl/ogl.h"
#include "ogl/ogl_constants.h"

#include "dataStructures/vector.h"
#include "renderer/framebuffer/FrameBuffer.h"

#include <stdexcept>
#include <type_traits>


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
        void setFramebufferSubData(
            GLenum target,GLint level,
            GLint xoffset,GLint yoffset,
            GLint x, GLint y,
            GLsizei width,GLsizei height,
            const FrameBuffer& fb
        );

        bool isPowerOfTwo() const;

        /**
         * @brief Get color directly from integer x and y coords
         */
        template<bool POWER_OF_TWO_SIZE = false>
        inline ColorCell queryByCoords(GLint w, GLint h) const{
            if constexpr (POWER_OF_TWO_SIZE){
                return m_data[((h & (m_texture_height_minus_1)) << m_width_log2) + (w & (m_texture_width_minus_1))];
            }
            else{
                return m_data[((h % m_texture_height) * m_texture_width) + (w % m_texture_width)];
            }
        }
        /**
         * Query a color using standard float x and y coords from interval [0; 1]
         *
         * Coordinates are expected to be non-negative
         */
        template<
            bool POWER_OF_TWO_SIZE = false,
            bool NON_NEGATIVE_COORDS = false
        >
        inline ColorCell sampleTex(float s_coord, float t_coord) const{

            switch (wrap_s)
            {
                case GL_REPEAT:
                    break;

                case GL_CLAMP:
                    s_coord = std::clamp(s_coord, 0.0f, 1.0f);
                    break;

                case GL_CLAMP_TO_EDGE:
                    s_coord = std::clamp(s_coord, 1.0f / (2 * m_texture_width), 1.0f - (1.0f / (2 * m_texture_width)));
                    break;

                default:
                    break;
            }
            switch (wrap_t)
            {
                case GL_REPEAT:
                    break;

                case GL_CLAMP:
                    t_coord = std::clamp(t_coord, 0.0f, 1.0f);
                    break;

                case GL_CLAMP_TO_EDGE:
                    t_coord = std::clamp(t_coord, 1.0f / (2 * m_texture_height), 1.0f - (1.0f / (2 * m_texture_height)));
                    break;

                default:
                    break;
            }
            // We only check the min filter

            // Nearest neighbour
            if (min_filter == GL_NEAREST){
                GLuint w = std::floor((m_texture_width) * s_coord);
                GLuint h = std::floor((m_texture_height) * t_coord);
                return queryByCoords<POWER_OF_TWO_SIZE>(w, h);
            }
            // Bilinear interpolation

            if constexpr (NON_NEGATIVE_COORDS){
                float w_f =( (m_texture_width) * s_coord) + 0.5;
                int w_0 = w_f;
                int w_1 = w_0 + 1;
                float dif = w_f - w_0;
                w_0--;
                w_1--;

                float h_f =( (m_texture_height) * t_coord) + 0.5;
                int h_0 = h_f;
                int h_1 = h_0 + 1;
                float dif_h = h_f - h_0;

                h_0--;
                h_1--;


                ColorCell c_00 = queryByCoords<POWER_OF_TWO_SIZE>(w_0, h_0);
                ColorCell c_01 = queryByCoords<POWER_OF_TWO_SIZE>(w_1, h_0);

                ColorCell c_10 = queryByCoords<POWER_OF_TWO_SIZE>(w_0, h_1);
                ColorCell c_11 = queryByCoords<POWER_OF_TWO_SIZE>(w_1, h_1);

                float blue_0  = (c_00.blue  + ((c_01.blue   - c_00.blue  ) * dif)), blue_1  = (c_10.blue   + ((c_11.blue   - c_10.blue  ) * dif));
                float green_0 = (c_00.green + ((c_01.green  - c_00.green ) * dif)), green_1 = (c_10.green  + ((c_11.green  - c_10.green ) * dif));
                float red_0   = (c_00.red   + ((c_01.red    - c_00.red   ) * dif)), red_1   = (c_10.red    + ((c_11.red    - c_10.red   ) * dif));
                float alpha_0 = (c_00.alpha + ((c_01.alpha  - c_00.alpha ) * dif)), alpha_1 = (c_10.alpha  + ((c_11.alpha  - c_10.alpha ) * dif));

                ColorCell ret{
                    static_cast<unsigned char>(blue_0  + ((blue_1  - blue_0)  * dif_h)),
                    static_cast<unsigned char>(green_0 + ((green_1 - green_0) * dif_h)),
                    static_cast<unsigned char>(red_0   + ((red_1   - red_0)   * dif_h)),
                    static_cast<unsigned char>(alpha_0 + ((alpha_1 - alpha_0) * dif_h))
                };

                return ret;
            }
            else{
                float w_f =( (m_texture_width) * s_coord) - 0.5;
                int w_0 = std::floor(w_f);
                int w_1 = w_0 + 1;
                float dif = std::abs(w_f - w_0);

                float h_f =( (m_texture_height) * t_coord) - 0.5;
                int h_0 = std::floor(h_f);
                int h_1 = h_0 + 1;
                float dif_h = std::abs(h_f - h_0);

                ColorCell c_00 = queryByCoords<POWER_OF_TWO_SIZE>(w_0, h_0);
                ColorCell c_01 = queryByCoords<POWER_OF_TWO_SIZE>(w_1, h_0);

                ColorCell c_10 = queryByCoords<POWER_OF_TWO_SIZE>(w_0, h_1);
                ColorCell c_11 = queryByCoords<POWER_OF_TWO_SIZE>(w_1, h_1);

                float blue_0  = (c_00.blue  + ((c_01.blue   - c_00.blue  ) * dif)), blue_1  = (c_10.blue   + ((c_11.blue   - c_10.blue  ) * dif));
                float green_0 = (c_00.green + ((c_01.green  - c_00.green ) * dif)), green_1 = (c_10.green  + ((c_11.green  - c_10.green ) * dif));
                float red_0   = (c_00.red   + ((c_01.red    - c_00.red   ) * dif)), red_1   = (c_10.red    + ((c_11.red    - c_10.red   ) * dif));
                float alpha_0 = (c_00.alpha + ((c_01.alpha  - c_00.alpha ) * dif)), alpha_1 = (c_10.alpha  + ((c_11.alpha  - c_10.alpha ) * dif));

                ColorCell ret{
                    static_cast<unsigned char>(blue_0  + ((blue_1  - blue_0)  * dif_h)),
                    static_cast<unsigned char>(green_0 + ((green_1 - green_0) * dif_h)),
                    static_cast<unsigned char>(red_0   + ((red_1   - red_0)   * dif_h)),
                    static_cast<unsigned char>(alpha_0 + ((alpha_1 - alpha_0) * dif_h))
                };

                return ret;
            }
        }

        template<typename T>
        void retrieveData(GLint level, GLenum format, T* out_data) const{
            T type_max;
            if constexpr (std::is_floating_point_v<T>){
                type_max = 1.0f;
            }
            else{
                type_max = std::numeric_limits<T>::max();
            }

            const auto scaleColor = [type_max](unsigned char val) -> T {
                return (static_cast<float>(val) / ColorCell::MAX_VALUE) * type_max;
            };
            size_t data_index = 0;
            for (size_t i = 0; i < m_data.size(); i++){
                switch (format){
                    case GL_RED:
                        out_data[data_index++] = scaleColor(m_data[i].red);
                        break;
                    case GL_GREEN:
                        out_data[data_index++] = scaleColor(m_data[i].green);
                        break;
                    case GL_BLUE:
                        out_data[data_index++] = scaleColor(m_data[i].blue);
                        break;
                    case GL_ALPHA:
                        out_data[data_index++] = scaleColor(m_data[i].alpha);
                        break;
                    case GL_RGB:
                        out_data[data_index++] = scaleColor(m_data[i].red);
                        out_data[data_index++] = scaleColor(m_data[i].green);
                        out_data[data_index++] = scaleColor(m_data[i].blue);
                        break;
                    case GL_RGBA:
                        out_data[data_index++] = scaleColor(m_data[i].red);
                        out_data[data_index++] = scaleColor(m_data[i].green);
                        out_data[data_index++] = scaleColor(m_data[i].blue);
                        out_data[data_index++] = scaleColor(m_data[i].alpha);
                        break;

                    default:
                        throw std::runtime_error("Unsupported color format");
                }
            }
        }

        GLuint getWidth() const;
        GLuint getHeight() const;

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
        GLuint m_width_log2;
        GLuint m_texture_width_minus_1;

        GLuint m_texture_height;
        GLuint m_height_log2;
        GLuint m_texture_height_minus_1;





};

} // namespace cgl
