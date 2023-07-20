#pragma once

/**
 * @file ogl_stencil.h
 * @brief Stencil buffer related functions
 */

#include "ogl_types.h"


#ifdef __cplusplus
extern "C" {
#endif

void glStencilFunc( GLenum func, GLint ref, GLuint mask );
void glStencilMask( GLuint mask );
void glStencilOp( GLenum fail, GLenum zfail, GLenum zpass );
void glClearStencil(GLint s);


#ifdef __cplusplus
}
#endif