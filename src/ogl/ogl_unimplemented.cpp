#include "ogl/ogl_unimplemented.h"
#include "utility/print.h"

#include "ogl/ogl_shared.h"
#include "renderer/Renderer.h"

void glFogf(GLenum pname, GLfloat param)
{
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setFogOption(pname, param);
    });
}
void glFogi(GLenum pname, GLint param)
{
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setFogOption(pname, param);
    });
}
void glFogfv(GLenum pname, const GLfloat* params)
{
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setFogOptionV(pname, params);
    });
}
void glFogiv(GLenum pname, const GLint* params){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setFogOptionV(pname, params);
    });
}

void glHint( GLenum target, GLenum mode ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    // #ifdef DEBUG
    // throw std::runtime_error("Unimplemented function");
    // #endif
}

void glBitmap(GLsizei width, GLsizei height,
              GLfloat xorig, GLfloat yorig,
              GLfloat xmove, GLfloat ymove,
              const GLubyte* bitmap
){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glReadPixels(
    GLint x, GLint y,
    GLsizei width, GLsizei height,
    GLenum format, GLenum type,
    GLvoid* pixels
){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glPixelStoref(GLenum pname, GLfloat param){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glPixelStorei(GLenum pname, GLint param){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glPointSize(GLfloat size){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glPolygonMode(GLenum face, GLenum mode){
    // Only fill is currently supported
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    // #ifdef DEBUG
    // throw std::runtime_error("Unimplemented function");
    // #endif
}
void glPolygonOffset(GLfloat factor, GLfloat units){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setPolygonOffset(factor, units);
    });
}

// Ignored

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setScissorBox(x, y, width, height);
    });
}
void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setColorMask( (red << 3) | (green << 2) | (blue < 1) | alpha);
    });
}

// Smooth is always used
void glShadeModel(GLenum mode){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    // #ifdef DEBUG
    // throw std::runtime_error("Unimplemented function");
    // #endif
}


void glClipPlane(GLenum plane, const GLdouble* equation){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glLineWidth(GLfloat width){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord1s(	GLenum target, GLshort s){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord1i(	GLenum target, GLint s){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord1f(	GLenum target, GLfloat s){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord1d(	GLenum target, GLdouble s){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord2s(	GLenum target, GLshort s, GLshort t){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord2i(	GLenum target, GLint s, GLint t){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord2f(	GLenum target, GLfloat s, GLfloat t){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord2d(	GLenum target, GLdouble s, GLdouble t){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord3s(	GLenum target, GLshort s, GLshort t, GLshort r){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord3i(	GLenum target, GLint s, GLint t, GLint r){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord3f(	GLenum target, GLfloat s, GLfloat t, GLfloat r){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord3d(	GLenum target, GLdouble s, GLdouble t, GLdouble r){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord4s(	GLenum target, GLshort s, GLshort t, GLshort r, GLshort q){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord4i(	GLenum target, GLint s, GLint t, GLint r, GLint q){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord4f(	GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMultiTexCoord4d(	GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMap2d(
    GLenum	   target,
    GLdouble	   u1,
    GLdouble	   u2,
    GLint	   ustride,
    GLint	   uorder,
    GLdouble	   v1,
    GLdouble	   v2,
    GLint	   vstride,
    GLint	   vorder,
    const GLdouble *points
){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glEvalMesh2(
	GLenum mode,
 	GLint i1,
 	GLint i2,
 	GLint j1,
 	GLint j2
){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glMapGrid2d(
    GLint un,
    GLdouble u1,
    GLdouble u2,
    GLint vn,
    GLdouble v1,
    GLdouble v2
){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}