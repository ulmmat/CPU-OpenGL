#include "renderer/textures/Texture.h"

#include <cmath>
#include <cstdio>
#include <stdexcept>

namespace cgl
{

void Texture::setData(
    GLenum target, GLint level,
    GLint internalFormat,
    GLsizei width, GLsizei height,
    GLint border, GLenum format, GLenum type,
    const GLvoid* pixels
){
    if (type != GL_BYTE && type != GL_UNSIGNED_BYTE){
        throw std::runtime_error("Unsupported pixel format");
    }
    const GLubyte* pixels_b = static_cast<const GLubyte*>(pixels);

    m_data.resize(width * height);
    m_texture_width = width;
    m_texture_height = height;
    size_t ctr = 0;
    if (format == GL_RGB){
        for (GLsizei i = 0; i < (width * height) * 3; i+= 3){
            m_data[ctr++] = ColorCell{
                .blue =  pixels_b[i + 2],
                .green = pixels_b[i + 1],
                .red =   pixels_b[i],
                .alpha = 255
            };
        }
    }
    else if (format == GL_RGBA){
        for (GLsizei i = 0; i < (width * height) * 4; i+= 4){
            m_data[ctr++] = ColorCell{
                .blue =  pixels_b[i + 2],
                .green = pixels_b[i + 1],
                .red =   pixels_b[i],
                .alpha = pixels_b[i + 3]
            };
        }
    }
    else{
        throw std::runtime_error("Unsupported texture format");
    }
}
void Texture::setSubData(
    GLenum target,GLint level,
    GLint xoffset,GLint yoffset,
    GLsizei width,GLsizei height,
    GLenum format,GLenum type,
    const GLvoid* pixels
){
    if (type != GL_BYTE && type != GL_UNSIGNED_BYTE){
        throw std::runtime_error("Unsupported pixel format");
    }
    const GLubyte* pixels_b = static_cast<const GLubyte*>(pixels);

    ColorCell* row;
    size_t i = 0;
    for (GLint y_off = yoffset; y_off < static_cast<GLint>(yoffset + height); y_off++){
        row = getRow(y_off);
        for (GLint x_off = xoffset; x_off < static_cast<GLint>(xoffset + width); x_off++){
            // i = (y_off * width) + x_off;
            if (format == GL_RGB){
                row[x_off] = ColorCell{
                    .blue = pixels_b[i + 2],
                    .green = pixels_b[i + 1],
                    .red = pixels_b[i],
                    .alpha = 255
                };
                i += 3;
            }
            else if (format == GL_RGBA){
                row[x_off] = ColorCell{
                    .blue =  pixels_b[i + 2],
                    .green = pixels_b[i + 1],
                    .red =   pixels_b[i],
                    .alpha = pixels_b[i + 3]
                };
                i += 4;
            }
        }
    }
}
}; // namespace cgl

