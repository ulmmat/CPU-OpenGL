#pragma once

#include "ogl/ogl_types.h"

#include <stdexcept>

namespace cgl
{
/**
 * @brief Class representing OpenGL buffers / pointers (eg. vertex pointer, color pointer)
 */
struct GenericBuffer{
    /**
     * Empty buffer
     */
    GenericBuffer();
    GenericBuffer(
        const GLvoid* ptr,
        GLenum data_type,
        GLsizei stride,
        GLint size
    );

    /**
     * @brief Get value from buffer
     *
     * Buffers are expected to be of type float.
     * This functions interprets the buffer directly as a float pointer.
     *
     * @param elem Index of element
     * @param index Index of value of that element
     */
    inline float directFloatAccess(GLsizei elem, GLsizei index){
        return static_cast<const GLfloat*>(ptr)[elem * stride_elem + index];
    }

    /**
     * @brief Get value from buffer
     *
     * Buffers are expected to be of type float.
     * This functions interprets the buffer directly as a float pointer.
     *
     * @param elem Index of element
     * @param index Index of value of that element
     */

    /**
     * @brief Get value from buffer as type T
     *
     * @param elem Index of element
     * @param index Index of value of that element
     */
    template<typename T>
    inline T castElement(GLsizei elem, GLsizei index){
        switch (data_type){
            case GL_BYTE :
                return static_cast<T>(static_cast<const GLbyte*>(ptr)[elem * stride_elem + index]);
                break;
            case GL_UNSIGNED_BYTE :
                return static_cast<T>(static_cast<const GLubyte*>(ptr)[elem * stride_elem + index]);
                break;
            case GL_SHORT :
                return static_cast<T>(static_cast<const GLshort*>(ptr)[elem * stride_elem + index]);
                break;
            case GL_UNSIGNED_SHORT :
                return static_cast<T>(static_cast<const GLushort*>(ptr)[elem * stride_elem + index]);
                break;
            case GL_INT :
                return static_cast<T>(static_cast<const GLint*>(ptr)[elem * stride_elem + index]);
                break;
            case GL_UNSIGNED_INT :
                return static_cast<T>(static_cast<const GLuint*>(ptr)[elem * stride_elem + index]);
                break;
            case GL_FLOAT :
                return static_cast<T>(static_cast<const GLfloat*>(ptr)[elem * stride_elem + index]);
                break;
            case GL_DOUBLE :
                return static_cast<T>(static_cast<const GLdouble*>(ptr)[elem * stride_elem + index]);
                break;

        }
        throw std::runtime_error("Invalid data type");
    }

    /** Data pointer */
    const GLvoid* ptr = nullptr;
    /** Underlying type */
    GLenum data_type;
    /** Stride in bytes */
    GLsizei stride;
    /** Size of each "element" in the buffer (eg. a vertex of 3 flots has size 3) */
    GLint size;
    /**
     * Stride in number of elements of underlaying type, calculated from stride, size and sizeof
     * Eg. if stride is 12, size is 3 and type is float (4), stride_elem is 12/3*4 = 1
     */
    GLsizei stride_elem;

};

} // namespace cgl
