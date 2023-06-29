#pragma once

/**
 * @file ogl_unimplemented.h
 * @brief Declaration of some currently unimplemented and uncategorized OpenGL functions
 */

#include "ogl_types.h"


#ifdef __cplusplus
extern "C" {
#endif

void glFogf(GLenum pname, GLfloat param);
void glFogi(GLenum pname, GLint param);
void glFogfv(GLenum pname, const GLfloat* params);
void glFogiv(GLenum pname, const GLint* params);

void glColorMask( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha );
void glScissor( GLint x, GLint y, GLsizei width, GLsizei height);
void glShadeModel( GLenum mode );
void glStencilFunc( GLenum func, GLint ref, GLuint mask );
void glStencilMask( GLuint mask );
void glStencilOp( GLenum fail, GLenum zfail, GLenum zpass );
void glClearStencil(GLint s);

void glHint( GLenum target, GLenum mode );

void glBitmap(GLsizei width, GLsizei height,
              GLfloat xorig, GLfloat yorig,
              GLfloat xmove, GLfloat ymove,
              const GLubyte *bitmap );

void glReadPixels(GLint x, GLint y,
                  GLsizei width, GLsizei height,
                  GLenum format, GLenum type,
                  GLvoid* pixels);

void glPixelStoref(GLenum pname, GLfloat param);
void glPixelStorei(GLenum pname, GLint param);

void glPointSize(GLfloat size);
void glPolygonMode(GLenum face, GLenum mode);
void glPolygonOffset(GLfloat factor, GLfloat units);

#ifdef __cplusplus
}
#endif