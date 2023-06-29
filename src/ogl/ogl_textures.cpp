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
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
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


}