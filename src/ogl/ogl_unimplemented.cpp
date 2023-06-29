#include "ogl/ogl_unimplemented.h"
#include "utility/print.h"

void glFogf(GLenum pname, GLfloat param)
{
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glFogi(GLenum pname, GLint param)
{
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glFogfv(GLenum pname, const GLfloat* params)
{
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glFogiv(GLenum pname, const GLint* params){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glHint( GLenum target, GLenum mode ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
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
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
}
void glPolygonOffset(GLfloat factor, GLfloat units){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

// Ignored

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
}
void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
}
void glShadeModel(GLenum mode){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
}
void glStencilFunc(GLenum func, GLint ref, GLuint mask){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
}
void glStencilMask(GLuint mask){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
}
void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
}
void glClearStencil(GLint s) {
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
}