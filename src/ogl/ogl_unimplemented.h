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


void glClipPlane(GLenum plane, const GLdouble* equation);

void glLineWidth(GLfloat width);

void glMultiTexCoord1s(	GLenum target,
 	GLshort s);

void glMultiTexCoord1i(	GLenum target,
 	GLint s);

void glMultiTexCoord1f(	GLenum target,
 	GLfloat s);

void glMultiTexCoord1d(	GLenum target,
 	GLdouble s);

void glMultiTexCoord2s(	GLenum target,
 	GLshort s,
 	GLshort t);

void glMultiTexCoord2i(	GLenum target,
 	GLint s,
 	GLint t);

void glMultiTexCoord2f(	GLenum target,
 	GLfloat s,
 	GLfloat t);

void glMultiTexCoord2d(	GLenum target,
 	GLdouble s,
 	GLdouble t);

void glMultiTexCoord3s(	GLenum target,
 	GLshort s,
 	GLshort t,
 	GLshort r);

void glMultiTexCoord3i(	GLenum target,
 	GLint s,
 	GLint t,
 	GLint r);

void glMultiTexCoord3f(	GLenum target,
 	GLfloat s,
 	GLfloat t,
 	GLfloat r);

void glMultiTexCoord3d(	GLenum target,
 	GLdouble s,
 	GLdouble t,
 	GLdouble r);

void glMultiTexCoord4s(	GLenum target,
 	GLshort s,
 	GLshort t,
 	GLshort r,
 	GLshort q);

void glMultiTexCoord4i(	GLenum target,
 	GLint s,
 	GLint t,
 	GLint r,
 	GLint q);

void glMultiTexCoord4f(	GLenum target,
 	GLfloat s,
 	GLfloat t,
 	GLfloat r,
 	GLfloat q);

void glMultiTexCoord4d(	GLenum target,
 	GLdouble s,
 	GLdouble t,
 	GLdouble r,
 	GLdouble q);

void glMap2d(
    GLenum target,
    GLdouble u1,
    GLdouble u2,
    GLint ustride,
    GLint uorder,
    GLdouble v1,
    GLdouble v2,
    GLint vstride,
    GLint vorder,
    const GLdouble *points
);

void glEvalMesh2(
	GLenum mode,
 	GLint i1,
 	GLint i2,
 	GLint j1,
 	GLint j2
);

void glMapGrid2d(
    GLint un,
    GLdouble u1,
    GLdouble u2,
    GLint vn,
    GLdouble v1,
    GLdouble v2
);

#ifdef __cplusplus
}
#endif