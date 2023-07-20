#include "ogl/ogl_stencil.h"
#include "ogl/ogl_shared.h"
#include "renderer/Renderer.h"
#include "utility/print.h"

void glStencilFunc(GLenum func, GLint ref, GLuint mask){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setStencilFunc(func, ref, mask);
    });
}
void glStencilMask(GLuint mask){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setStencilMask(mask);
    });
}
void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setStencilOp(fail, zfail, zpass);
    });
}
void glClearStencil(GLint s) {
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setStencilClear(s);
    });
}
