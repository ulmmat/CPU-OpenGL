#pragma once

#include "dataStructures/vector.h"
#include "dataStructures/vectors.h"
#include "renderer/framebuffer/ColorCell.h"

#include <algorithm>
#include <limits>

namespace cgl
{

using DepthCell = float;
using StencCell = uint8_t;

constexpr StencCell STENC_CELL_MASK = std::numeric_limits<StencCell>::max();

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
    Vector<DepthCell> depth_buffer;
    Vector<StencCell> stencil_buffer;
};

} // namespace cgl
