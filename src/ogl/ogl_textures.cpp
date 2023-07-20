#include "ogl_types.h"
#include "utility/print.h"
#include "ogl/ogl_shared.h"
#include "renderer/Renderer.h"

extern "C" {

void glGenTextures( GLsizei n, GLuint* textures ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.generateTextures(n, textures);
    });
}

void glBindTexture( GLenum target, GLuint texture ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.bindTexture(texture);
    });
}

void glDeleteTextures( GLsizei n, const GLuint* textures){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.deleteTextures(n, textures);
    });
}

void glTexEnvf( GLenum target, GLenum pname, GLfloat param ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    glTexEnvi(target, pname, param);
}
void glTexEnvi( GLenum target, GLenum pname, GLint param ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setTextureEnv(param);
    });
}

void glTexImage2D( GLenum target, GLint level,
                   GLint internal_format,
                   GLsizei width, GLsizei height,
                   GLint border, GLenum format, GLenum type,
                   const GLvoid* pixels
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
            renderer.setTexture(target, level,
            internal_format,
            width, height,
            border, format, type,
            pixels
        );
    });
}
void glTexSubImage2D( GLenum target, GLint level,
                      GLint xoffset, GLint yoffset,
                      GLsizei width, GLsizei height,
                      GLenum format, GLenum type,
                      const GLvoid* pixels )
{
    withRenderer([&](cgl::Renderer& renderer){
        renderer.subTexture(target, level, xoffset, yoffset, width, height, format, type, pixels);
    });
}

void glTexParameteri( GLenum target, GLenum pname, GLint param ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setTextureParameter(target, pname, param);
    });
}

void glTexParameterf( GLenum target, GLenum pname, GLfloat param ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setTextureParameter(target, pname, param);
    });
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glGetTexParameteriv(GLenum target, GLenum pname, GLint *params){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glCopyTexSubImage2D(
    GLenum target, GLint level,
    GLint xoffset, GLint yoffset,
    GLint x, GLint y,
    GLsizei width, GLsizei height
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.copyFramebufferToTex(target, level, xoffset, yoffset, x, y, width, height);
    });
}

void glGetTexImage(
    GLenum target,
    GLint level,
    GLenum format,
    GLenum type,
    GLvoid *pixels
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        switch (type)
        {
            case GL_UNSIGNED_BYTE:
                renderer.getTexture(target)->retrieveData<GLubyte>(level, format, static_cast<GLubyte*>(pixels));
                break;
            case GL_BYTE:
                renderer.getTexture(target)->retrieveData<GLbyte>(level, format, static_cast<GLbyte*>(pixels));
                break;
            case GL_UNSIGNED_SHORT:
                renderer.getTexture(target)->retrieveData<GLushort>(level, format, static_cast<GLushort*>(pixels));
                break;
            case GL_SHORT:
                renderer.getTexture(target)->retrieveData<GLshort>(level, format, static_cast<GLshort*>(pixels));
                break;
            case GL_UNSIGNED_INT:
                renderer.getTexture(target)->retrieveData<GLuint>(level, format, static_cast<GLuint*>(pixels));
                break;
            case GL_INT:
                renderer.getTexture(target)->retrieveData<GLint>(level, format, static_cast<GLint*>(pixels));
                break;
            case GL_FLOAT:
                renderer.getTexture(target)->retrieveData<GLfloat>(level, format, static_cast<GLfloat*>(pixels));
                break;
            default:
                break;
        }
    });
}


}