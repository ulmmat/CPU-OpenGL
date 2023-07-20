#pragma once

/**
 * @file ogl_textures.h
 * @brief Functions related to texturing
 */

#include "ogl_types.h"

#ifdef __cplusplus
extern "C" {
#endif



void glGenTextures( GLsizei n, GLuint* textures );

void glBindTexture( GLenum target, GLuint texture );

void glDeleteTextures( GLsizei n, const GLuint* textures);

void glTexEnvf( GLenum target, GLenum pname, GLfloat param );
void glTexEnvi( GLenum target, GLenum pname, GLint param );

void glTexImage2D( GLenum target, GLint level,
                   GLint internalFormat,
                   GLsizei width, GLsizei height,
                   GLint border, GLenum format, GLenum type,
                   const GLvoid* pixels );

void glTexSubImage2D( GLenum target, GLint level,
                      GLint xoffset, GLint yoffset,
                      GLsizei width, GLsizei height,
                      GLenum format, GLenum type,
                      const GLvoid* pixels );
void glTexParameteri( GLenum target, GLenum pname, GLint param );
void glTexParameterf( GLenum target, GLenum pname, GLfloat param );

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params);
void glGetTexParameteriv(GLenum target, GLenum pname, GLint *params);

void glCopyTexSubImage2D(
    GLenum target, GLint level,
    GLint xoffset, GLint yoffset,
    GLint x, GLint y,
    GLsizei width, GLsizei height
);
void glGetTexImage(
    GLenum target,
    GLint level,
    GLenum format,
    GLenum type,
    GLvoid *pixels
);


#ifdef __cplusplus
}
#endif