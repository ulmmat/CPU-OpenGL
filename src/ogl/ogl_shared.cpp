#include "ogl/ogl_shared.h"
#include "ogl/GLContext.h"

cgl::GLContext* getCurrentContext(){
    return cgl::cur_context;
}
void withContext(std::function<void(cgl::GLContext&)> fun){
    cgl::GLContext* ctx = getCurrentContext();
    if (ctx){
        fun(*ctx);
    }
}

cgl::Renderer* getCurrentRenderer(){
    if (!cgl::cur_context){
        return nullptr;
    }
    return &cgl::cur_context->renderer;
}
void withRenderer(std::function<void(cgl::Renderer&)> fun){
    cgl::Renderer* renderer = getCurrentRenderer();
    if (renderer){
        fun(*renderer);
    }
}