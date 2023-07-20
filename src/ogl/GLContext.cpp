#include "ogl/GLContext.h"

#include "utility/time/Stopwatch.h"

namespace cgl
{

GLContext::~GLContext(){
    #ifdef GLX
    clearImages();
    #endif
}
#ifdef GLX
void GLContext::clearImages(){
    for (auto& p : backend_images){
        p.second->data = nullptr;
        XDestroyImage(p.second);
    }
}
void GLContext::createImage(Display* display, Visual* vis, int depth, int width, int height){
    this->height = height;
    this->width = width;
    renderer.resizeFramebuffers(width, height);
    #ifdef GLX
    Map<GLenum, FrameBuffer*> fbs = renderer.getFramebuffers();
    clearImages();
    for (const auto& p : fbs){
        backend_images[p.first] = XCreateImage(display, vis, depth, ZPixmap, 0, reinterpret_cast<char*>(p.second->color_buffer.data()), width, height, 32, 0);
    }
    #endif

}
XImage* GLContext::getReadImage() const{
    auto it = backend_images.find(renderer.getReadFramebuffer());
    if (it != backend_images.end()){
        return it->second;
    }
    return nullptr;
}

XImage* GLContext::getDrawImage() const{
    auto it = backend_images.find(renderer.getDrawFramebuffer());
    if (it != backend_images.end()){
        return it->second;
    }
    return nullptr;
}
#endif


#ifdef WGL

void GLContext::setHandle(HDC handle){
    device_handle = handle;

    HGDIOBJ hBitmap = GetCurrentObject(handle, OBJ_BITMAP);
    HDC  new_handle = CreateCompatibleDC(handle);



    BITMAP bitmap_hdr;
    memset(&bitmap_hdr, 0, sizeof(BITMAP));

    GetObject(hBitmap, sizeof(BITMAP), &bitmap_hdr);

    width = 0;
    height = 0;

    width = bitmap_hdr.bmWidth;
    height = bitmap_hdr.bmHeight;

    renderer.resizeFramebuffers(width, height);

    resizeDIBs(width, height);
}

GLContext::FramebufferDIB GLContext::createDIB(const FrameBuffer* framebuffer, int width, int height){
    GLContext::FramebufferDIB ret;
    HDC new_handle = CreateCompatibleDC(device_handle);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    HBITMAP bitmap = CreateDIBSection(new_handle, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&ret.dib_data), NULL, NULL);
    ret.dib_bitmap = bitmap;
    ret.extra_handle = new_handle;
    ret.fb = framebuffer;

    return ret;
}
const GLContext::FramebufferDIB* GLContext::getDrawDIB() const{
    auto it = framebuffer_dibs.find(renderer.getDrawFramebuffer());
    if (it != framebuffer_dibs.end()){
        return &(it->second);
    }
    return nullptr;
}
void GLContext::clearDIBs(){
    for (const auto& p : framebuffer_dibs) {
        int res = DeleteObject(p.second.dib_bitmap);
        res = ReleaseDC(0, p.second.extra_handle);
    }
    framebuffer_dibs.clear();
}

void GLContext::resizeDIBs(int width, int height) {
    clearDIBs();
    Map<GLenum, FrameBuffer*> fbs = renderer.getFramebuffers();
    for (const auto& p : fbs) {
        framebuffer_dibs[p.first] = createDIB(p.second, width, height);
    }
}
#endif


void GLContext::flushFramebuffer(){
    static Stopwatch frametime;
    coutPrintDebug("Flushing framebuffer");
    Rasterizer::DrawStats stats = renderer.fetchFrameStats();
    coutPrint(
        "Drawn tris: ", stats.handled_tris,
        "Discarded tris: ", stats.discarded_tris,
        "Fragments: ", stats.handled_fragments,
        "Drawn Fragments: ", stats.drawn_fragments,
        "FPS: ", 1000000.0f / frametime.micros()
    );
    frametime.reset();
    #ifdef GLX

    /**
     * Draws the draw XImage over the window. The data of XImage is set to the underlying color famebuffer,
     * The data is thus updated automatically when drawing.
     */

    XPutImage(display, draw_buffer, gc, getDrawImage(), 0, 0, 0, 0, width, height);
    #endif

    #ifdef WGL
    const FramebufferDIB* dib = getDrawDIB();

    if (!dib || width != dib->fb->width || height != dib->fb->height) {
        width = dib->fb->width;
        height = dib->fb->height;
        resizeDIBs(width, height);
        dib = &framebuffer_dibs[renderer.getDrawFramebuffer()];
    }
    SelectObject(dib->extra_handle, dib->dib_bitmap);

    memcpy(dib->dib_data, dib->fb->color_buffer.data(), width * height * 4);

    BitBlt(device_handle, 0, 0, width, height, dib->extra_handle, 0, 0, SRCCOPY);
    GdiFlush();
    #endif
}

}
