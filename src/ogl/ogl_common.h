#include "ogl_types.h"
#include "ogl_constants.h"
#include "ogl_textures.h"
#include "ogl_begin.h"
#include "ogl/ogl_alpha.h"
#include "ogl/ogl_matrices.h"

#ifdef __cplusplus
extern "C" {
#endif

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

void glClear( GLbitfield mask );
void glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );

void glClearStencil( GLint s );
void glColor4f( GLfloat red, GLfloat green,
                GLfloat blue, GLfloat alpha );



void glEnable( GLenum cap );
void glDisable( GLenum cap );

void glFinish( void );
void glFlush( void );

void glDepthFunc( GLenum func );
void glDepthMask( GLboolean flag );
void glDepthRange( GLclampd near_val, GLclampd far_val );

void glCullFace( GLenum mode );

void glGetFloatv(GLenum pname, GLfloat* params);
void glGetDoublev(GLenum pname, GLdouble* params);
void glGetIntegerv(GLenum pname, GLint* params);
void glGetBooleanv(GLenum pname, GLboolean* params);
const GLubyte* glGetString( GLenum name );

GLenum glGetError( void );

#ifdef __cplusplus
}
#endif