#ifdef GLX

#include "backends/glx/glx.h"
#include "backends/glx/GLXConfig.h"
#include "ogl/ogl.h"


#include "dataStructures/string.h"
#include "dataStructures/map.h"

#define GLX_USE_GL		        1
#define GLX_BUFFER_SIZE		    2
#define GLX_LEVEL		        3
#define GLX_RGBA		        4
#define GLX_DOUBLEBUFFER	    5
#define GLX_STEREO		        6
#define GLX_AUX_BUFFERS		    7
#define GLX_RED_SIZE		    8
#define GLX_GREEN_SIZE		    9
#define GLX_BLUE_SIZE		    10
#define GLX_ALPHA_SIZE		    11
#define GLX_DEPTH_SIZE		    12
#define GLX_STENCIL_SIZE	    13
#define GLX_ACCUM_RED_SIZE	    14
#define GLX_ACCUM_GREEN_SIZE	15
#define GLX_ACCUM_BLUE_SIZE	    16
#define GLX_ACCUM_ALPHA_SIZE	17

#define TRUE_COLOR_CLASS 4
#define DIRECT_COLOR_CLASS 5

cgl::String attribToString(int v){
    switch(v){
        case GLX_USE_GL:
            return "GLX_USE_GL";
            break;
        case GLX_BUFFER_SIZE:
            return "GLX_BUFFER_SIZE";
            break;
        case GLX_LEVEL:
            return "GLX_LEVEL";
            break;
        case GLX_RGBA:
            return "GLX_RGBA";
            break;
        case GLX_DOUBLEBUFFER:
            return "GLX_DOUBLEBUFFER";
            break;
        case GLX_STEREO:
            return "GLX_STEREO";
            break;
        case GLX_AUX_BUFFERS:
            return "GLX_AUX_BUFFERS";
            break;
        case GLX_RED_SIZE:
            return "GLX_RED_SIZE";
            break;
        case GLX_GREEN_SIZE:
            return "GLX_GREEN_SIZE";
            break;
        case GLX_BLUE_SIZE:
            return "GLX_BLUE_SIZE";
            break;
        case GLX_ALPHA_SIZE:
            return "GLX_ALPHA_SIZE";
            break;
        case GLX_DEPTH_SIZE:
            return "GLX_DEPTH_SIZE";
            break;
        case GLX_STENCIL_SIZE:
            return "GLX_STENCIL_SIZE";
            break;
        case GLX_ACCUM_RED_SIZE:
            return "GLX_ACCUM_RED_SIZE";
            break;
        case GLX_ACCUM_GREEN_SIZE:
            return "GLX_ACCUM_GREEN_SIZE";
            break;
        case GLX_ACCUM_BLUE_SIZE:
            return "GLX_ACCUM_BLUE_SIZE";
            break;
        case GLX_ACCUM_ALPHA_SIZE:
            return "GLX_ACCUM_ALPHA_SIZE";
            break;
    }
    return "UNKNOWN";
}

const cgl::Map<cgl::String, void*> PROC_ADDRESS_MAP = {
    {"glXChooseVisual", reinterpret_cast<void*>(&glXChooseVisual)},
    {"glXCreateContext", reinterpret_cast<void*>(&glXCreateContext)},
    {"glXDestroyContext", reinterpret_cast<void*>(&glXDestroyContext)},
    {"glXMakeCurrent", reinterpret_cast<void*>(&glXMakeCurrent)},
    {"glXSwapBuffers", reinterpret_cast<void*>(&glXSwapBuffers)},
    {"glXQueryDrawable", reinterpret_cast<void*>(&glXQueryDrawable)}
};

void* glXGetProcAddressARB (const GLubyte* fun){
    auto it = PROC_ADDRESS_MAP.find(cgl::String(reinterpret_cast<const char*>(fun)));
    if (it != PROC_ADDRESS_MAP.end()){
        cgl::coutPrintDebug("Found: ", it->second);
        return it->second;
    }
    return nullptr;
}


void glXSwapBuffers(
    Display* dpy,
 	GLXDrawable drawable
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    glFlush();
}

int glXQueryDrawable(
    Display* dpy,
 	GLXDrawable draw,
 	int attribute,
 	unsigned int* valu
){
    throw std::runtime_error("Unimplemented");
}


XVisualInfo* glXChooseVisual(
    Display* dpy,
 	int screen,
 	const int* attrib_list
){
    XVisualInfo info;
    info.screen = screen;
    int res_cnt;
    XVisualInfo* infos = XGetVisualInfo(dpy, screen, &info, &res_cnt);
    for (int i = 0; i < res_cnt; i++){

        if (infos[i].c_class == DIRECT_COLOR_CLASS){
            infos[0] = infos[i];
            break;
        }
    }

    return infos;
}

GLXFBConfig* glXChooseFBConfig(
    Display* dpy,
 	int screen,
 	const int* attrib_list,
 	int* nelements
){
    XVisualInfo info;
    info.screen = screen;
    int res_cnt;
    XVisualInfo* infos = XGetVisualInfo(dpy, screen, &info, &res_cnt);
    global_cfg.config_vis_infos = infos;
    global_cfg.reset();
    for (int i = 0; i < res_cnt; i++){
        global_cfg.configs.emplace_back(reinterpret_cast<GLXFBConfig>(i));
    }

    *nelements = global_cfg.configs.size();
    GLXFBConfig* ret_array = new GLXFBConfig[*nelements];
    memcpy(ret_array, global_cfg.configs.data(), sizeof(GLXFBConfig) * *nelements);
    return ret_array;
}

GLXContext glXCreateNewContext(
    Display* dpy,
 	GLXFBConfig config,
 	int render_type,
 	GLXContext share_list,
 	Bool direct
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    cgl::GLContext* ctx = *cgl::contexts.insert(new cgl::GLContext).first;
    ctx->display = dpy;
    return ctx;
}

GLXContext glXCreateContext(
    Display* dpy,
 	XVisualInfo* vis,
 	GLXContext shareList,
 	Bool direct
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    cgl::GLContext* ctx = *cgl::contexts.insert(new cgl::GLContext).first;
    ctx->display = dpy;
    return ctx;
}

void glXDestroyContext(
    Display* dpy,
 	GLXContext ctx
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    cgl::contexts.erase(static_cast<cgl::GLContext*>(ctx));
}

GLXContext glXGetCurrentContext()
{
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    return cgl::cur_context;
}

Bool glXMakeCurrent(
    Display* d,
 	GLXDrawable drawable,
 	GLXContext ctx
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    auto it = cgl::contexts.find(static_cast<cgl::GLContext*>(ctx));
    if (it == cgl::contexts.end()){
        return false;
    }
    cgl::GLContext* context = *it;
    cgl::cur_context = context;

    context->draw_buffer = reinterpret_cast<XID>(drawable);
    global_cfg.display = d;

    if (!context->gc){
        context->gc = XCreateGC(global_cfg.display, context->draw_buffer, 0,0);
    }

    // We expect that the draw Drawable is a simple XWindow
    XWindowAttributes attrs;
    XGetWindowAttributes(global_cfg.display, (XID)drawable, &attrs);
    XImage* cur_image = context->getDrawImage();
    if (!cur_image ||
         cur_image->width  != attrs.width ||
         cur_image->height != attrs.height
    ){
        context->createImage(global_cfg.display, attrs.visual, attrs.depth, attrs.width, attrs.height);
    }


    return true;
}

Bool glXMakeContextCurrent(
    Display* d,
 	GLXDrawable draw,
 	GLXDrawable read,
 	GLXContext ctx
){
    auto it = cgl::contexts.find(static_cast<cgl::GLContext*>(ctx));
    if (it == cgl::contexts.end()){
        return false;
    }
    cgl::GLContext* context = *it;
    cgl::cur_context = context;

    context->draw_buffer = reinterpret_cast<XID>(draw);
    global_cfg.display = d;
    if (!context->gc){
        context->gc = XCreateGC(global_cfg.display, context->draw_buffer, 0,0);
    }

    // We expect that the draw Drawable is a simple XWindow
    XWindowAttributes attrs;
    XGetWindowAttributes(global_cfg.display, (XID)draw, &attrs);
    XImage* cur_image = context->getDrawImage();

    // If an XImage was not yet created, or if the drawable has been resized, recreate it
    if (!cur_image ||
         cur_image->width  != attrs.width ||
         cur_image->height != attrs.height
    ){
        context->createImage(global_cfg.display, attrs.visual, attrs.depth, attrs.width, attrs.height);
    }

    cgl::coutPrintDebug(__FUNCTION__, "Called");

    return true;
}

Bool glXQueryExtension(
    Display* dpy,
 	int* error_base_ptr,
 	int* event_base_ptr
){
    int major_op, error_base_dummy, event_base_dummy;
    if (!error_base_ptr){
        error_base_ptr = &error_base_dummy;
    }
    if (!event_base_ptr){
        event_base_ptr = &event_base_dummy;
    }
    Bool ret = XQueryExtension(dpy, "GLX", &major_op, error_base_ptr, event_base_ptr);
    return ret;
}

Bool glXIsDirect(
    Display* dpy,
    GLXContext ctx
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    return false;
}

int glXGetFBConfigAttrib(
    Display* dpy,
 	GLXFBConfig config,
 	int attribute,
 	int* value
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    return 0;
}

XVisualInfo* glXGetVisualFromFBConfig(
    Display* dpy,
 	GLXFBConfig config
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    return global_cfg.config_vis_infos + reinterpret_cast<size_t>(config);
}


#endif