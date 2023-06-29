#pragma once

/**
 * @file glx.h
 * @brief Functions for interfacing with X11
 *
 * These functions are the bare minimum for glut and SDL to work,
 * with fragile implementations. Should be improved.
 */

#ifdef GLX

#include <iostream>
#include <sstream>
#include <string>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "ogl/ogl_types.h"
#include "dataStructures/vector.h"
#include "dataStructures/map.h"

#include "utility/print.h"
#include "ogl/GLContext.h"

extern "C" {

using GLXFBConfig = void*;
using GLXDrawable = void*;
using GLXContext = void*;

/**
 * @brief Load function by name
 *
 * Currently, only functions requested by SDL are returned
 */
void* glXGetProcAddressARB (const GLubyte* fun);

void glXSwapBuffers(
    Display* dpy,
 	GLXDrawable drawable
);
/**
 * Requested, but not called by SDL,
 * currently unimplemented.
 */
int glXQueryDrawable(
    Display* dpy,
 	GLXDrawable draw,
 	int attribute,
 	unsigned int* valu
);

/**
 * Returns a visual info available for the display + screen
 * that fits the passed key - value attributes passed in attrib_last
 */
XVisualInfo* glXChooseVisual(
    Display* dpy,
 	int screen,
 	const int* attrib_list
);

/**
 * Basically a more updated version of glXChooseVisual, that is basically implemented in the same way
 */
GLXFBConfig* glXChooseFBConfig(
    Display* dpy,
 	int screen,
 	const int* attrib_list,
 	int* nelements
);



/////// Context functions

/**
 * Create a new OpenGL context from a previously selected visual
 */
GLXContext glXCreateContext(
    Display* dpy,
 	XVisualInfo* vis,
 	GLXContext shareList,
 	Bool direct
);

/**
 * Create a new OpenGL context from a previously selected GLXFBConfig
 *
 * A more modern version of glXCreateContext that pairs with glXChooseFBConfig
 */
GLXContext glXCreateNewContext(
    Display* dpy,
 	GLXFBConfig config,
 	int render_type,
 	GLXContext share_list,
 	Bool direct
);

/**
 * Destroy passed context
 */
void glXDestroyContext(
    Display* dpy,
 	GLXContext ctx
);

/**
 * Get currently selected OpenGL context
 */
GLXContext glXGetCurrentContext();

/**
 * Make an OpenGL context current
 *
 * If the drawable has resized from the last call,
 * the framebuffers are automatically resized
 *
 * GLXDrawable may point to different types, but only XWindow is supported
 */
Bool glXMakeCurrent(
    Display* d,
 	GLXDrawable drawable,
 	GLXContext ctx
);

/**
 * Make an OpenGL context current
 *
 * A newer version of glXMakeCurrent, where the drawables may by of more
 * different types, though only XWindow is still supported
 *
 * A read drawable is ignored - reading OpenGL functions are currently unimplemented
 */
Bool glXMakeContextCurrent(
	Display* d,
 	GLXDrawable draw,
 	GLXDrawable read,
 	GLXContext ctx
);
Bool glXQueryExtension(
    Display* dpy,
 	int* errorBase,
 	int* eventBase
);

/**
 * Returns false - the buffer is copied using X commands
 */
Bool glXIsDirect(
    Display* dpy,
    GLXContext ctx
);

/**
 * Unimplemented, returns 0
 */
int glXGetFBConfigAttrib(
    Display* dpy,
 	GLXFBConfig config,
 	int attribute,
 	int* value
);

XVisualInfo* glXGetVisualFromFBConfig(
    Display* dpy,
 	GLXFBConfig config
);

};


#endif