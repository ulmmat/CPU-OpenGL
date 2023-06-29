#include "renderer/framebuffer/FrameBuffer.h"
#include "utility/print.h"

namespace cgl
{


void FrameBuffer::resizeFramebuffer(int width, int height){
    this->width = width;
    this->height = height;

    color_buffer.resize(width * height, ColorCell{0, 0, 0});
    depth_buffer.resize(width * height, 1.0f);

    return;
}

} // namespace cgl
