#include "renderer/GenericBuffer.h"

#include <stdexcept>


namespace cgl
{

template<typename T>
void setElemStride(GLsizei& elem_stride, GLsizei& stride, GLsizei size){
    if (stride == 0){
        stride = sizeof(T) * size;
    }
    elem_stride = stride / sizeof(T);

    /**
     * Buffer is interpreted as an array of elements of size == sizeof(data_type) * size,
     * with stride allowing skipping of some of them.
     *
     * If this is not met, throw an exception
     */
    if ((stride % sizeof(T)) != 0){
        throw std::runtime_error("Invalid stride");
    }
}

GenericBuffer::GenericBuffer(){

}
GenericBuffer::GenericBuffer(
    const GLvoid* c_ptr,
    GLenum c_data_type,
    GLsizei c_stride,
    GLint c_size
) :
    ptr(c_ptr),
    data_type(c_data_type),
    stride(c_stride),
    size(c_size)
{
    switch (data_type){
        case GL_BYTE :
            setElemStride<GLbyte>(stride_elem, stride, size);
            break;
        case GL_UNSIGNED_BYTE :
            setElemStride<GLubyte>(stride_elem, stride, size);
            break;
        case GL_SHORT :
            setElemStride<GLshort>(stride_elem, stride, size);
            break;
        case GL_UNSIGNED_SHORT :
            setElemStride<GLushort>(stride_elem, stride, size);
            break;
        case GL_INT :
            setElemStride<GLint>(stride_elem, stride, size);
            break;
        case GL_UNSIGNED_INT :
            setElemStride<GLuint>(stride_elem, stride, size);
            break;
        case GL_FLOAT :
            setElemStride<GLfloat>(stride_elem, stride, size);
            break;
        case GL_DOUBLE :
            setElemStride<GLdouble>(stride_elem, stride, size);
            break;
        default:
            throw std::runtime_error("Invalid data type");
            break;
    }
}



} // namespace cgl
