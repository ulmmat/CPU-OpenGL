#include "ogl.h"
#include "ogl_constants.h"
#include "utility/print.h"
#include "ogl/GLContext.h"
#include "dataStructures/vector.h"
#include "dataStructures/optional.h"
#include "ogl/ogl_shared.h"


void glViewport(GLint x, GLint y, GLsizei width, GLsizei height){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.resizeFramebuffers(width, height);
    });
}

void glDepthFunc( GLenum func ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setDepthFunc(func);
    });
}
void glDepthMask( GLboolean flag ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setDepthMask(flag);
    });
}
void glDepthRange( GLclampd near_val, GLclampd far_val ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setDepthRange(near_val, far_val);
    });
}


void glClear( GLbitfield mask ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.clear();
    });
}
void glEnable(GLenum cap ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    cgl::Renderer* renderer = getCurrentRenderer();
    if (renderer){
        renderer->setCapability(cap, true);
    }
}
void glDisable(GLenum cap ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    cgl::Renderer* renderer = getCurrentRenderer();
    if (renderer){
        renderer->setCapability(cap, false);
    }
}


/**
 * All calls execute immediately
 */
void glFinish( void ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    return;
}

void glFlush( void ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withContext([](cgl::GLContext& ctx){
        ctx.flushFramebuffer();
    });
}

void glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setClearColor(cgl::Vec4{red, green, blue, alpha});
    });
}

void glCullFace( GLenum mode ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setBackfaceCullMode(mode);
    });
}


void glGetFloatv(
    GLenum	 pname,
    GLfloat	 *params
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    if (pname == 0x0BA6 /*GL_MODELVIEW_MATRIX*/){
        withRenderer([&](cgl::Renderer& renderer){
            memcpy(params, glm::value_ptr(renderer.getMatrixStack().modelview_stack.top()), sizeof(GLfloat) * 16);
        });
    }
    else if (pname == 0x0BA7 /*GL_PROJECTION_MATRIX*/){
        withRenderer([&](cgl::Renderer& renderer){
            memcpy(params, glm::value_ptr(renderer.getMatrixStack().projection_stack.top()), sizeof(GLfloat) * 16);
        });
    }
    else{
        throw std::runtime_error("Unsupported param name");
    }
}
void glGetDoublev(GLenum pname, GLdouble* params){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    return;
}
void glGetIntegerv(GLenum pname, GLint* params){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    return;
}
void glGetBooleanv(GLenum pname, GLboolean* params){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    return;
}


/**
 * Error handling is currently unimplemented
 */
GLenum glGetError( void ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    return 0;
}

const GLubyte* glGetString( GLenum name ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    switch (name)
    {
        case GL_VENDOR :
            return reinterpret_cast<const GLubyte*>("CUSTOM");
            break;
        case GL_RENDERER :
            return reinterpret_cast<const GLubyte*>("CUSTOM RENDERER");
            break;
        case GL_VERSION :
            return reinterpret_cast<const GLubyte*>("1.4");
            break;
        case GL_EXTENSIONS :
            return reinterpret_cast<const GLubyte*>("");
            break;
        default:
            break;
    }
    return nullptr;
}