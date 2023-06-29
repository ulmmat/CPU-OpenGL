#pragma once

/**
 * @file wgl.h
 * @brief Functions for interfacing with WGL on Windows
 *
 * These functions are the bare minimum for glut and SDL to work,
 * with fragile implementations. Should be improved.
 */

#ifdef WGL

#include <iostream>
#include <sstream>
#include <string>

#include <windows.h>

#include "ogl/ogl_types.h"
#include "dataStructures/vector.h"
#include "dataStructures/map.h"

#include "utility/print.h"
#include "ogl/GLContext.h"




extern "C" {



__declspec(dllexport) HGLRC wglCreateContext(HDC handle);
__declspec(dllexport) BOOL wglDeleteContext(HGLRC unnamedParam1);
__declspec(dllexport) BOOL wglMakeCurrent(HDC unnamedParam1, HGLRC unnamedParam2);
__declspec(dllexport) PROC wglGetProcAddress(LPCSTR unnamedParam1);
__declspec(dllexport) BOOL wglShareLists(HGLRC unnamedParam1, HGLRC unnamedParam2);
__declspec(dllexport) HDC wglGetCurrentDC();
__declspec(dllexport) HGLRC wglGetCurrentContext();

__declspec(dllexport) int wglChoosePixelFormat(HDC hdc, const PIXELFORMATDESCRIPTOR* ppfd);
__declspec(dllexport) int wglDescribePixelFormat(HDC hdc, int iPixelFormat, UINT nBytes,LPPIXELFORMATDESCRIPTOR ppfd);
__declspec(dllexport) int wglGetPixelFormat(HDC hdc);
__declspec(dllexport) BOOL wglSetPixelFormat(HDC hdc, int format, const PIXELFORMATDESCRIPTOR* ppfd);
__declspec(dllexport) BOOL wglSwapBuffers(HDC unnamedParam1);

__declspec(dllexport) BOOL wglChoosePixelFormatARB(
    HDC hdc,
    const int* piAttribIList,
    const FLOAT* pfAttribFList,
    UINT nMaxFormats,
    int* piFormats,
    UINT* nNumFormat
);

};

#endif