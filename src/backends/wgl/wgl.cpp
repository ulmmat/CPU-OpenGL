#ifdef WGL

#include "backends/wgl/wgl.h"
#include "dataStructures/map.h"
#include "dataStructures/string.h"
#include <stdexcept>

int dummy_pixel_format = 1;

int wglChoosePixelFormat(HDC hdc, const PIXELFORMATDESCRIPTOR* ppfd) {
    return dummy_pixel_format;
}
int wglDescribePixelFormat(HDC hdc, int iPixelFormat, UINT nBytes, LPPIXELFORMATDESCRIPTOR ppfd) {
    return dummy_pixel_format;
}
int wglGetPixelFormat(HDC hdc) {
    return dummy_pixel_format;
}
BOOL wglSetPixelFormat(HDC hdc, int format, const PIXELFORMATDESCRIPTOR* ppfd) {
    return true;
}
BOOL wglSwapBuffers(HDC handle) {
    glFlush();
    return true;
}

BOOL wglChoosePixelFormatARB(HDC hdc,
    const int* piAttribIList,
    const FLOAT* pfAttribFList,
    UINT nMaxFormats,
    int* piFormats,
    UINT* nNumFormat
) {
    *piFormats = dummy_pixel_format;
    *nNumFormat = 1;
    return true;
}

BOOL wglGetPixelFormatAttribivARB(HDC hdc,
    int iPixelFormat,
    int iLayerPlane,
    UINT nAttributes,
    const int* piAttributes,
    int* piValues
){
    return true;
}

const char* wglGetExtensionsStringARB(HDC hdc) {
    return "WGL_ARB_pixel_format";
}

cgl::Map<cgl::String, void*> PROC_MAP = {
    {"wglGetExtensionsStringARB", &wglGetExtensionsStringARB},
    {"wglChoosePixelFormatARB", &wglChoosePixelFormatARB},
    {"wglGetPixelFormatAttribivARB", &wglGetPixelFormatAttribivARB}
};

HMODULE this_library = nullptr;

PROC wglGetProcAddress(LPCSTR proc_name) {
    if (!this_library){
        this_library = LoadLibraryW(L"./opengl32.dll");
    }
    auto it = PROC_MAP.find(cgl::String(proc_name));
    if (it != PROC_MAP.end()) {
        return reinterpret_cast<PROC>(it->second);
    }
    if (this_library){
        return GetProcAddress(this_library, proc_name);
    }
    return nullptr;
}

HGLRC wglCreateContext(HDC handle){
    cgl::GLContext* ctx = *cgl::contexts.insert(new cgl::GLContext).first;
    ctx->device_handle = handle;

    BITMAP structBitmapHeader;
    memset( &structBitmapHeader, 0, sizeof(BITMAP) );

    HGDIOBJ hBitmap = GetCurrentObject(handle, OBJ_BITMAP);

    GetObject(hBitmap, sizeof(BITMAP), &structBitmapHeader);
    return reinterpret_cast<HGLRC>(ctx);
}
BOOL wglDeleteContext(HGLRC ctx){
    return (cgl::contexts.erase(reinterpret_cast<cgl::GLContext*>(ctx)) == 1);
}
BOOL wglMakeCurrent(HDC handle, HGLRC ctx) {
    if (!ctx){
        cgl::cur_context = nullptr;
        return true;
    }
    auto it = cgl::contexts.find(reinterpret_cast<cgl::GLContext*>(ctx));
    if (it == cgl::contexts.end()) {
        return false;
    }
    cgl::GLContext* context = *it;
    cgl::cur_context = context;

    context->setHandle(handle);

    return true;
}

BOOL wglShareLists(HGLRC unnamedParam1, HGLRC unnamedParam2){
    return false;
}

HDC wglGetCurrentDC(){
    return cgl::cur_context->device_handle;
}

HGLRC wglGetCurrentContext(){
    return reinterpret_cast<HGLRC>(cgl::cur_context);
}

#endif