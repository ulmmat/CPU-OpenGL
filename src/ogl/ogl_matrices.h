#pragma once

/**
 * @file ogl_matrices.h
 * @brief Functions related matrix modification
 */

#include "ogl_types.h"

#ifdef __cplusplus
extern "C" {
#endif


void glMatrixMode(GLenum mode);
void glLoadIdentity();

void glPushMatrix( void );
void glPopMatrix( void );

void gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
void gluLookAt(	GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
 	            GLdouble centerX, GLdouble centerY, GLdouble centerZ,
 	            GLdouble upX, GLdouble upY, GLdouble upZ);
void gluOrtho2D (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);


void glLoadMatrixd(const GLdouble* m);
void glLoadMatrixf(const GLfloat* m);

void glOrtho(GLdouble left, GLdouble right,
             GLdouble bottom, GLdouble top,
             GLdouble near_val, GLdouble far_val);
void glFrustum( GLdouble left, GLdouble right,
                GLdouble bottom, GLdouble top,
                GLdouble near_val, GLdouble far_val );

void glRotated( GLdouble angle, GLdouble x, GLdouble y, GLdouble z );
void glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z );

void glScaled( GLdouble x, GLdouble y, GLdouble z );
void glScalef( GLfloat x, GLfloat y, GLfloat z );

void glTranslated( GLdouble x, GLdouble y, GLdouble z );
void glTranslatef( GLfloat x, GLfloat y, GLfloat z );

void glMultMatrixd(const GLdouble* m);
void glMultMatrixf(const GLfloat* m);


#ifdef __cplusplus
}
#endif