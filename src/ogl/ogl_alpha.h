#pragma once

/**
 * @file ogl_alpha.h
 * @brief Functions related to alpha channel functions (alpha testing, blending)
 */


#include "ogl_types.h"
extern "C" {

void glAlphaFunc( GLenum func, GLclampf ref );
void glBlendFunc( GLenum sfactor, GLenum dfactor );

}