#pragma once

#include "dataStructures/stack.h"
#include "dataStructures/map.h"
#include "dataStructures/vectors.h"

#include "ogl/ogl_constants.h"

namespace cgl
{

using MatStack = Stack<Mat4>;

/**
 * Various matrix stacks used by the OpenGL standard
 */
struct MatrixStacks{


    MatStack modelview_stack{std::deque<Mat4>{IDENTITY_MAT}};
    MatStack projection_stack{std::deque<Mat4>{IDENTITY_MAT}};
    MatStack texture_stack{std::deque<Mat4>{IDENTITY_MAT}};

    /** Map OpenGL constants to stack */
    const Map<GLenum, MatStack*> MODE_STACK_MAP = {
        {GL_MODELVIEW, &modelview_stack},
        {GL_PROJECTION, &projection_stack},
        {GL_TEXTURE, &texture_stack},
    };
};

} // namespace cgl
