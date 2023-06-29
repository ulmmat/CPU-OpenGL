#pragma once

/**
 * @file ogl_buffers.h
 * @brief Functions for setting buffer pointer and related drawing functions
 */

#define __gl_h_

#include "ogl_types.h"
#include "ogl_constants.h"
#include "ogl_textures.h"
#include "ogl_begin.h"

#ifdef __cplusplus
extern "C" {
#endif

void glEnableClientState( GLenum cap );

void glDisableClientState( GLenum cap );

void glPushClientAttrib( GLbitfield mask );

void glPopClientAttrib( void );

void glPushAttrib( GLbitfield mask );

void glPopAttrib( void );


void glVertexPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* ptr );

void glNormalPointer( GLenum type, GLsizei stride, const GLvoid* ptr );

void glColorPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* ptr );

void glIndexPointer( GLenum type, GLsizei stride, const GLvoid* ptr );

void glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* ptr );

void glEdgeFlagPointer( GLsizei stride, const GLvoid* ptr );

void glGetPointerv( GLenum pname, GLvoid **params );

void glArrayElement( GLint i );

void glDrawArrays( GLenum mode, GLint first, GLsizei count );

void glDrawBuffer( GLenum mode );
void glReadBuffer( GLenum mode );

void glDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices );

void glInterleavedArrays( GLenum format, GLsizei stride, const GLvoid* pointer );


#ifdef __cplusplus
}
#endif