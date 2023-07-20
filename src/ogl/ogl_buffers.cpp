#include "ogl/ogl_alpha.h"
#include "utility/print.h"
#include "ogl/ogl_shared.h"
#include "renderer/Renderer.h"

void glEnableClientState(GLenum cap){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setClientState(cap, true);
    });
}

void glDisableClientState(GLenum cap){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setClientState(cap, false);
    });
}

void glPushClientAttrib( GLbitfield mask ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glPopClientAttrib( void ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glPushAttrib( GLbitfield mask ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glPopAttrib( void ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glVertexPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* ptr ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setGenericBuffer(
            cgl::Renderer::BufferType::VERTEX,
            cgl::GenericBuffer{ptr, type, stride, size}
        );
    });
}

void glNormalPointer( GLenum type, GLsizei stride, const GLvoid* ptr ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.setGenericBuffer(
            cgl::Renderer::BufferType::NORMAL,
            cgl::GenericBuffer{static_cast<const GLfloat*>(ptr), type, stride, 3}
        );
    });
}


void glColorPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* ptr ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.setGenericBuffer(
            cgl::Renderer::BufferType::COLOR,
            cgl::GenericBuffer{static_cast<const GLfloat*>(ptr), type, stride, size}
        );
    });
}

void glIndexPointer( GLenum type, GLsizei stride, const GLvoid* ptr ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.setGenericBuffer(
            cgl::Renderer::BufferType::COLOR,
            cgl::GenericBuffer{static_cast<const GLfloat*>(ptr), type, stride, 1}
        );
    });
}

void glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* ptr ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.setGenericBuffer(
            cgl::Renderer::BufferType::TEX_COORD,
            cgl::GenericBuffer{static_cast<const GLfloat*>(ptr), type, stride, size}
        );
    });
}

void glEdgeFlagPointer( GLsizei stride, const GLvoid* ptr ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setGenericBuffer(
            cgl::Renderer::BufferType::EDGE,
            cgl::GenericBuffer{static_cast<const GLfloat*>(ptr), GL_BYTE, stride, 1}
        );
    });
}

void glGetPointerv( GLenum pname, GLvoid **params ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glArrayElement(GLint i){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setVertexArrayElem(i);
    });
}

void glDrawArrays( GLenum mode, GLint first, GLsizei count ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.drawArrays(mode, first, count);
    });
}
void glDrawBuffer( GLenum mode ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.setDrawFramebuffer(mode);
    });
}
void glReadBuffer( GLenum mode ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setReadFramebuffer(mode);
    });
}

void glDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        switch (type)
        {
            case GL_UNSIGNED_BYTE :
                renderer.drawElements<GLubyte>(mode, count, type, static_cast<const GLubyte*>(indices));
                break;
            case GL_UNSIGNED_SHORT  :
                renderer.drawElements<GLushort>(mode, count, type, static_cast<const GLushort*>(indices));
                break;
            case GL_UNSIGNED_INT :
                renderer.drawElements<GLuint>(mode, count, type, static_cast<const GLuint*>(indices));
                break;

            default:
                break;
        }

    });
}

void glInterleavedArrays( GLenum format, GLsizei stride, const GLvoid* pointer ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}