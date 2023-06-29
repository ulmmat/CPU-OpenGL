#include "ogl/ogl_begin.h"
#include "utility/print.h"
#include "ogl/ogl_shared.h"
#include "renderer/Renderer.h"
#include <limits>


void glBegin( GLenum mode ){
    using namespace cgl;
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    PrimitiveType typed_mode = static_cast<PrimitiveType>(mode);
    withRenderer([&](cgl::Renderer& renderer){
        renderer.beginDraw(typed_mode);
    });
}
void glEnd( void ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.endDraw();
    });
}

void addVertex3(GLfloat x, GLfloat y, GLfloat z = 0.0f){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.addVertex(cgl::Vec3{x, y, z});
    });
}
void addVertex4(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    x /= w;
    y /= w;
    z /= w;

    withRenderer([&](cgl::Renderer& renderer){
        renderer.addVertex(cgl::Vec3{x, y, z});
    });
}
void glVertex2d( GLdouble x, GLdouble y ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(x, y);
}
void glVertex2f( GLfloat x, GLfloat y ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(x, y);
}
void glVertex2i( GLint x, GLint y ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(x, y);
}
void glVertex2s( GLshort x, GLshort y ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(x, y);
}
void glVertex3d( GLdouble x, GLdouble y, GLdouble z ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(x, y, z);
}
void glVertex3f( GLfloat x, GLfloat y, GLfloat z ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(x, y, z);
}
void glVertex3i( GLint x, GLint y, GLint z ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(x, y, z);
}
void glVertex3s( GLshort x, GLshort y, GLshort z ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(x, y, z);
}
void glVertex4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(x, y, z);
}
void glVertex4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex4(x, y, z, w);
}
void glVertex4i( GLint x, GLint y, GLint z, GLint w ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex4(x, y, z, w);
}
void glVertex4s( GLshort x, GLshort y, GLshort z, GLshort w ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex4(x, y, z, w);
}
void glVertex2dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glVertex2fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(v[0], v[1]);
}
void glVertex2iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(v[0], v[1]);
}
void glVertex2sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(v[0], v[1]);
}
void glVertex3dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(v[0], v[1], v[2]);
}
void glVertex3fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(v[0], v[1], v[2]);
}
void glVertex3iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(v[0], v[1], v[2]);
}
void glVertex3sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex3(v[0], v[1], v[2]);
}
void glVertex4dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex4(v[0], v[1], v[2], v[3]);
}
void glVertex4fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex4(v[0], v[1], v[2], v[3]);
}
void glVertex4iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex4(v[0], v[1], v[2], v[3]);
}
void glVertex4sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    addVertex4(v[0], v[1], v[2], v[3]);
}


template<typename T>
void setNormalIntegerSigned(T red, T green, T blue){
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setVertexNormal(
            cgl::Vec3{
                static_cast<GLfloat>(red)   / std::numeric_limits<T>::max(),
                static_cast<GLfloat>(green) / std::numeric_limits<T>::max(),
                static_cast<GLfloat>(blue)  / std::numeric_limits<T>::max()
            }
        );
    });
}

template<typename T>
void setNormalIntegerUnsigned(T red, T green, T blue){
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setVertexNormal(
            cgl::Vec3{
                (2.0*(static_cast<GLfloat>(red)   / std::numeric_limits<T>::max())) - 1.0f,
                (2.0*(static_cast<GLfloat>(green) / std::numeric_limits<T>::max())) - 1.0f,
                (2.0*(static_cast<GLfloat>(blue)  / std::numeric_limits<T>::max())) - 1.0f
            }
        );
    });
}

void glNormal3b( GLbyte nx, GLbyte ny, GLbyte nz ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setNormalIntegerSigned(nx, ny, nz);
}
void glNormal3d( GLdouble nx, GLdouble ny, GLdouble nz ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setVertexNormal(
            cgl::Vec3{
                static_cast<GLfloat>(nx),
                static_cast<GLfloat>(ny),
                static_cast<GLfloat>(nz)
            }
        );
    });
}
void glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setVertexNormal(
            cgl::Vec3{
                nx,
                ny,
                nz
            }
        );
    });
}
void glNormal3i( GLint nx, GLint ny, GLint nz ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setNormalIntegerSigned(nx, ny, nz);
}
void glNormal3s( GLshort nx, GLshort ny, GLshort nz ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setNormalIntegerSigned(nx, ny, nz);
}
void glNormal3bv( const GLbyte* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setNormalIntegerSigned(v[0], v[1], v[2]);
}
void glNormal3dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setVertexNormal(
            cgl::Vec3{
                static_cast<GLfloat>(v[0]),
                static_cast<GLfloat>(v[1]),
                static_cast<GLfloat>(v[2])
            }
        );
    });
}
void glNormal3fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setVertexNormal(
            cgl::Vec3{
                v[0],
                v[1],
                v[2]
            }
        );
    });
}
void glNormal3iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setNormalIntegerSigned(v[0], v[1], v[2]);
}
void glNormal3sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setNormalIntegerSigned(v[0], v[1], v[2]);
}
void glIndexd( GLdouble c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glIndexf( GLfloat c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glIndexi( GLint c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glIndexs( GLshort c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glIndexub( GLubyte c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glIndexdv( const GLdouble* c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glIndexfv( const GLfloat* c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glIndexiv( const GLint* c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glIndexsv( const GLshort* c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glIndexubv( const GLubyte* c ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

template<typename T>
void setColorInteger3(T red, T green, T blue){
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                static_cast<GLfloat>(red)   / std::numeric_limits<T>::max(),
                static_cast<GLfloat>(green) / std::numeric_limits<T>::max(),
                static_cast<GLfloat>(blue)  / std::numeric_limits<T>::max(),
                1.0f
            }
        );
    });
}
template<typename T>
void setColorInteger4(T red, T green, T blue, T alpha){
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                static_cast<GLfloat>(red)   / std::numeric_limits<T>::max(),
                static_cast<GLfloat>(green) / std::numeric_limits<T>::max(),
                static_cast<GLfloat>(blue)  / std::numeric_limits<T>::max(),
                static_cast<GLfloat>(alpha)  / std::numeric_limits<T>::max()
            }
        );
    });
}
void glColor3b( GLbyte red, GLbyte green, GLbyte blue ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3<GLbyte>(red, green, blue);
}
void glColor3d( GLdouble red, GLdouble green, GLdouble blue ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                static_cast<float>(red),
                static_cast<float>(green),
                static_cast<float>(blue),
                1.0f
            }
        );
    });
}
void glColor3f( GLfloat red, GLfloat green, GLfloat blue ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                red,
                green,
                blue,
                1.0f
            }
        );
    });
}
void glColor3i( GLint red, GLint green, GLint blue ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3<GLint>(red, green, blue);
}
void glColor3s( GLshort red, GLshort green, GLshort blue ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3<GLint>(red, green, blue);
}
void glColor3ub( GLubyte red, GLubyte green, GLubyte blue ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3<GLint>(red, green, blue);
}
void glColor3ui( GLuint red, GLuint green, GLuint blue ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3<GLint>(red, green, blue);
}
void glColor3us( GLushort red, GLushort green, GLushort blue ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3<GLint>(red, green, blue);
}


void glColor4b( GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(red, green, blue, alpha);
}
void glColor4d( GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                static_cast<float>(red),
                static_cast<float>(green),
                static_cast<float>(blue),
                static_cast<float>(alpha)
            }
        );
    });
}
void glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                red,
                green,
                blue,
                alpha
            }
        );
    });
}
void glColor4i( GLint red, GLint green, GLint blue, GLint alpha ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(red, green, blue, alpha);
}
void glColor4s( GLshort red, GLshort green, GLshort blue, GLshort alpha ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(red, green, blue, alpha);
}
void glColor4ub( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(red, green, blue, alpha);
}
void glColor4ui( GLuint red, GLuint green, GLuint blue, GLuint alpha ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(red, green, blue, alpha);
}
void glColor4us( GLushort red, GLushort green, GLushort blue, GLushort alpha ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(red, green, blue, alpha);
}


void glColor3bv( const GLbyte* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3(v[0], v[1], v[2]);
}
void glColor3dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                static_cast<float>(v[0]),
                static_cast<float>(v[1]),
                static_cast<float>(v[2]),
                1.0f
            }
        );
    });
}
void glColor3fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                v[0],
                v[1],
                v[2],
                1.0f
            }
        );
    });
}
void glColor3iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3(v[0], v[1], v[2]);
}
void glColor3sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3(v[0], v[1], v[2]);
}
void glColor3ubv( const GLubyte* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3(v[0], v[1], v[2]);
}
void glColor3uiv( const GLuint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3(v[0], v[1], v[2]);
}
void glColor3usv( const GLushort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger3(v[0], v[1], v[2]);
}
void glColor4bv( const GLbyte* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(v[0], v[1], v[2], v[3]);
}
void glColor4dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                static_cast<float>(v[0]),
                static_cast<float>(v[1]),
                static_cast<float>(v[2]),
                static_cast<float>(v[3])
            }
        );
    });
}
void glColor4fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMainColor(
            cgl::Vec4{
                v[0],
                v[1],
                v[2],
                v[3]
            }
        );
    });
}
void glColor4iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(v[0], v[1], v[2], v[3]);
}
void glColor4sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(v[0], v[1], v[2], v[3]);
}
void glColor4ubv( const GLubyte* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(v[0], v[1], v[2], v[3]);
}
void glColor4uiv( const GLuint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(v[0], v[1], v[2], v[3]);
}
void glColor4usv( const GLushort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    setColorInteger4(v[0], v[1], v[2], v[3]);
}
void glTexCoord1d( GLdouble s ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord1f( GLfloat s ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord1i( GLint s ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord1s( GLshort s ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord2d( GLdouble s, GLdouble t ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.setVertexTexCoords(
            cgl::Vec2{s, t}
        );
    });
}
void glTexCoord2f( GLfloat s, GLfloat t ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    glTexCoord2d(s, t);
}
void glTexCoord2i( GLint s, GLint t ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    glTexCoord2d(s, t);
}
void glTexCoord2s( GLshort s, GLshort t ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    glTexCoord2d(s, t);
}
void glTexCoord3d( GLdouble s, GLdouble t, GLdouble r ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord3f( GLfloat s, GLfloat t, GLfloat r ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord3i( GLint s, GLint t, GLint r ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord3s( GLshort s, GLshort t, GLshort r ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord4d( GLdouble s, GLdouble t, GLdouble r, GLdouble q ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord4f( GLfloat s, GLfloat t, GLfloat r, GLfloat q ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord4i( GLint s, GLint t, GLint r, GLint q ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord4s( GLshort s, GLshort t, GLshort r, GLshort q ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord1dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord1fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord1iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord1sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord2dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord2fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord2iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord2sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord3dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord3fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord3iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord3sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord4dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord4fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord4iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glTexCoord4sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos2d( GLdouble x, GLdouble y ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos2f( GLfloat x, GLfloat y ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos2i( GLint x, GLint y ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos2s( GLshort x, GLshort y ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos3d( GLdouble x, GLdouble y, GLdouble z ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos3f( GLfloat x, GLfloat y, GLfloat z ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos3i( GLint x, GLint y, GLint z ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos3s( GLshort x, GLshort y, GLshort z ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos4i( GLint x, GLint y, GLint z, GLint w ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos4s( GLshort x, GLshort y, GLshort z, GLshort w ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos2dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos2fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos2iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos2sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos3dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos3fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos3iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos3sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos4dv( const GLdouble* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos4fv( const GLfloat* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos4iv( const GLint* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRasterPos4sv( const GLshort* v ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRectd( GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2 ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRectf( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRecti( GLint x1, GLint y1, GLint x2, GLint y2 ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRects( GLshort x1, GLshort y1, GLshort x2, GLshort y2 ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRectdv( const GLdouble* v1, const GLdouble* v2 ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRectfv( const GLfloat* v1, const GLfloat* v2 ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRectiv( const GLint* v1, const GLint* v2 ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glRectsv( const GLshort* v1, const GLshort* v2 ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}