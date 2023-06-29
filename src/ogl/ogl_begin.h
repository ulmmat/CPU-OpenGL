#pragma once

/**
 * @file ogl_begin.h
 * @brief Functions related to glBegin / glEnd "transactions"
 */

#include "ogl_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void glBegin( GLenum mode );
void glEnd( void );


void glVertex2d( GLdouble x, GLdouble y );
void glVertex2f( GLfloat x, GLfloat y );
void glVertex2i( GLint x, GLint y );
void glVertex2s( GLshort x, GLshort y );

void glVertex3d( GLdouble x, GLdouble y, GLdouble z );
void glVertex3f( GLfloat x, GLfloat y, GLfloat z );
void glVertex3i( GLint x, GLint y, GLint z );
void glVertex3s( GLshort x, GLshort y, GLshort z );

void glVertex4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w );
void glVertex4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
void glVertex4i( GLint x, GLint y, GLint z, GLint w );
void glVertex4s( GLshort x, GLshort y, GLshort z, GLshort w );

void glVertex2dv( const GLdouble* v);
void glVertex2fv( const GLfloat* v);
void glVertex2iv( const GLint* v);
void glVertex2sv( const GLshort* v);

void glVertex3dv( const GLdouble* v);
void glVertex3fv( const GLfloat* v);
void glVertex3iv( const GLint* v);
void glVertex3sv( const GLshort* v);

void glVertex4dv( const GLdouble* v);
void glVertex4fv( const GLfloat* v);
void glVertex4iv( const GLint* v);
void glVertex4sv( const GLshort* v);


void glNormal3b( GLbyte nx, GLbyte ny, GLbyte nz );
void glNormal3d( GLdouble nx, GLdouble ny, GLdouble nz );
void glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz );
void glNormal3i( GLint nx, GLint ny, GLint nz );
void glNormal3s( GLshort nx, GLshort ny, GLshort nz );

void glNormal3bv( const GLbyte* v);
void glNormal3dv( const GLdouble* v);
void glNormal3fv( const GLfloat* v);
void glNormal3iv( const GLint* v);
void glNormal3sv( const GLshort* v);


void glIndexd( GLdouble c );
void glIndexf( GLfloat c );
void glIndexi( GLint c );
void glIndexs( GLshort c );
void glIndexub( GLubyte c );  /* 1.1 */

void glIndexdv( const GLdouble* c);
void glIndexfv( const GLfloat* c);
void glIndexiv( const GLint* c);
void glIndexsv( const GLshort* c);
void glIndexubv( const GLubyte* c);  /* 1.1 */

void glColor3b( GLbyte red, GLbyte green, GLbyte blue );
void glColor3d( GLdouble red, GLdouble green, GLdouble blue );
void glColor3f( GLfloat red, GLfloat green, GLfloat blue );
void glColor3i( GLint red, GLint green, GLint blue );
void glColor3s( GLshort red, GLshort green, GLshort blue );
void glColor3ub( GLubyte red, GLubyte green, GLubyte blue );
void glColor3ui( GLuint red, GLuint green, GLuint blue );
void glColor3us( GLushort red, GLushort green, GLushort blue );

void glColor4b( GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha );
void glColor4d( GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha );
void glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
void glColor4i( GLint red, GLint green, GLint blue, GLint alpha );
void glColor4s( GLshort red, GLshort green, GLshort blue, GLshort alpha );
void glColor4ub( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha );
void glColor4ui( GLuint red, GLuint green, GLuint blue, GLuint alpha );
void glColor4us( GLushort red, GLushort green, GLushort blue, GLushort alpha );


void glColor3bv( const GLbyte* v);
void glColor3dv( const GLdouble* v);
void glColor3fv( const GLfloat* v);
void glColor3iv( const GLint* v);
void glColor3sv( const GLshort* v);
void glColor3ubv( const GLubyte* v);
void glColor3uiv( const GLuint* v);
void glColor3usv( const GLushort* v);

void glColor4bv( const GLbyte* v);
void glColor4dv( const GLdouble* v);
void glColor4fv( const GLfloat* v);
void glColor4iv( const GLint* v);
void glColor4sv( const GLshort* v);
void glColor4ubv( const GLubyte* v);
void glColor4uiv( const GLuint* v);
void glColor4usv( const GLushort* v);


void glTexCoord1d( GLdouble s );
void glTexCoord1f( GLfloat s );
void glTexCoord1i( GLint s );
void glTexCoord1s( GLshort s );

void glTexCoord2d( GLdouble s, GLdouble t );
void glTexCoord2f( GLfloat s, GLfloat t );
void glTexCoord2i( GLint s, GLint t );
void glTexCoord2s( GLshort s, GLshort t );

void glTexCoord3d( GLdouble s, GLdouble t, GLdouble r );
void glTexCoord3f( GLfloat s, GLfloat t, GLfloat r );
void glTexCoord3i( GLint s, GLint t, GLint r );
void glTexCoord3s( GLshort s, GLshort t, GLshort r );

void glTexCoord4d( GLdouble s, GLdouble t, GLdouble r, GLdouble q );
void glTexCoord4f( GLfloat s, GLfloat t, GLfloat r, GLfloat q );
void glTexCoord4i( GLint s, GLint t, GLint r, GLint q );
void glTexCoord4s( GLshort s, GLshort t, GLshort r, GLshort q );

void glTexCoord1dv( const GLdouble* v);
void glTexCoord1fv( const GLfloat* v);
void glTexCoord1iv( const GLint* v);
void glTexCoord1sv( const GLshort* v);

void glTexCoord2dv( const GLdouble* v);
void glTexCoord2fv( const GLfloat* v);
void glTexCoord2iv( const GLint* v);
void glTexCoord2sv( const GLshort* v);

void glTexCoord3dv( const GLdouble* v);
void glTexCoord3fv( const GLfloat* v);
void glTexCoord3iv( const GLint* v);
void glTexCoord3sv( const GLshort* v);

void glTexCoord4dv( const GLdouble* v);
void glTexCoord4fv( const GLfloat* v);
void glTexCoord4iv( const GLint* v);
void glTexCoord4sv( const GLshort* v);


void glRasterPos2d( GLdouble x, GLdouble y );
void glRasterPos2f( GLfloat x, GLfloat y );
void glRasterPos2i( GLint x, GLint y );
void glRasterPos2s( GLshort x, GLshort y );

void glRasterPos3d( GLdouble x, GLdouble y, GLdouble z );
void glRasterPos3f( GLfloat x, GLfloat y, GLfloat z );
void glRasterPos3i( GLint x, GLint y, GLint z );
void glRasterPos3s( GLshort x, GLshort y, GLshort z );

void glRasterPos4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w );
void glRasterPos4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
void glRasterPos4i( GLint x, GLint y, GLint z, GLint w );
void glRasterPos4s( GLshort x, GLshort y, GLshort z, GLshort w );

void glRasterPos2dv( const GLdouble* v);
void glRasterPos2fv( const GLfloat* v);
void glRasterPos2iv( const GLint* v);
void glRasterPos2sv( const GLshort* v);

void glRasterPos3dv( const GLdouble* v);
void glRasterPos3fv( const GLfloat* v);
void glRasterPos3iv( const GLint* v);
void glRasterPos3sv( const GLshort* v);

void glRasterPos4dv( const GLdouble* v);
void glRasterPos4fv( const GLfloat* v);
void glRasterPos4iv( const GLint* v);
void glRasterPos4sv( const GLshort* v);


void glRectd( GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2 );
void glRectf( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 );
void glRecti( GLint x1, GLint y1, GLint x2, GLint y2 );
void glRects( GLshort x1, GLshort y1, GLshort x2, GLshort y2 );


void glRectdv( const GLdouble* v1, const GLdouble* v2 );
void glRectfv( const GLfloat* v1, const GLfloat* v2 );
void glRectiv( const GLint* v1, const GLint* v2 );
void glRectsv( const GLshort* v1, const GLshort* v2 );

#ifdef __cplusplus
}
#endif