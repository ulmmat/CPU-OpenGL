#include "ogl/ogl_alpha.h"
#include "utility/print.h"
#include "ogl/ogl_shared.h"
#include "renderer/Renderer.h"

void glBlendFunc( GLenum sfactor, GLenum dfactor ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setBlending(sfactor, dfactor);
    });
}
void glAlphaFunc( GLenum func, float ref ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setAlphaFunc(func, ref);
    });

}