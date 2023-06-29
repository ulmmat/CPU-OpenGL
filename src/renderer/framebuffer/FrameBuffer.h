#pragma once

#include "dataStructures/vector.h"
#include "dataStructures/vectors.h"
#include "renderer/framebuffer/ColorCell.h"

#include <algorithm>
#include <limits>

namespace cgl
{


/**
 * Representation of a framebuffer, currently a color and depth buffer
 */
struct FrameBuffer{

    /**
     * Resize all buffers
     */
    void resizeFramebuffer(int width, int height);

    unsigned width;
    unsigned height;

    Vector<ColorCell> color_buffer;
    Vector<float> depth_buffer;
};

} // namespace cgl
