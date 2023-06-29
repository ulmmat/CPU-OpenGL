#include "renderer/Renderer.h"

#include "utility/print.h"
#include "ogl/ogl_matrices.h"
#include "ogl/ogl_shared.h"

#ifdef __cplusplus
extern "C" {
#endif


void glMatrixMode(GLenum mode){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.setMatrixStack(mode);
    });
}
void glLoadIdentity(){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.setCurMatrix(cgl::IDENTITY_MAT);
    });
}

void glPushMatrix( void ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.pushMatrix();
    });
}
void glPopMatrix( void ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.popMatrix();
    });
}

void gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.perspectiveMat(glm::radians(fovy), aspect, zNear, zFar);
    });
}
void gluLookAt(	GLdouble eye_x, GLdouble eye_y, GLdouble eye_z,
 	            GLdouble center_x, GLdouble center_y, GLdouble center_z,
 	            GLdouble up_x, GLdouble up_y, GLdouble up_z
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.setCurMatrix(
            glm::lookAt(
                cgl::Vec3{eye_x, eye_y, eye_z},
                cgl::Vec3{center_x, center_y, center_z},
                cgl::Vec3{up_x, up_y, up_z}
            )
        );
    });
}
void gluOrtho2D (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    glOrtho(left, right, bottom, top, -1, 1);
}


void glLoadMatrixd(const GLdouble* m){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        cgl::Mat4 new_mat;
        float* mat_ptr = glm::value_ptr(new_mat);
        for (uint8_t i = 0; i < 16; i++){
            mat_ptr[i] = m[i];
        }
        renderer.setCurMatrix(new_mat);
    });
}
void glLoadMatrixf(const GLfloat* m){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        cgl::Mat4 new_mat;
        float* mat_ptr = glm::value_ptr(new_mat);
        for (uint8_t i = 0; i < 16; i++){
            mat_ptr[i] = m[i];
        }
        renderer.setCurMatrix(new_mat);
    });
}

void glOrtho(GLdouble left, GLdouble right,
             GLdouble bottom, GLdouble top,
             GLdouble near_val, GLdouble far_val
){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    withRenderer([&](cgl::Renderer& renderer){
        renderer.orthoMat(left, right, bottom, top, near_val, far_val);
    });
}
void glFrustum( GLdouble left, GLdouble right,
                GLdouble bottom, GLdouble top,
                GLdouble near_val, GLdouble far_val
){
    withRenderer([&](cgl::Renderer& renderer){
        renderer.frustumMat(left, right, bottom, top, near_val, far_val);
    });
}
void glRotated( GLdouble angle, GLdouble x, GLdouble y, GLdouble z ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.rotateMat(glm::radians(angle), x, y, z);
    });
}
void glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");
    if (angle == 0){
        return;
    }

    withRenderer([&](cgl::Renderer& renderer){
        renderer.rotateMatd(glm::radians(angle), x, y, z);
    });
}

void glScaled( GLdouble x, GLdouble y, GLdouble z ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}
void glScalef( GLfloat x, GLfloat y, GLfloat z ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");
    #ifdef DEBUG
    throw std::runtime_error("Unimplemented function");
    #endif
}

void glTranslated( GLdouble x, GLdouble y, GLdouble z ){
    cgl::coutPrintDebug(__FUNCTION__, "Unimplemented");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.translateMatd(x, y, z);
    });
}
void glTranslatef( GLfloat x, GLfloat y, GLfloat z ){
    cgl::coutPrintDebug(__FUNCTION__, "Called");

    withRenderer([&](cgl::Renderer& renderer){
        renderer.translateMat(x, y, z);
    });
}


#ifdef __cplusplus
}
#endif