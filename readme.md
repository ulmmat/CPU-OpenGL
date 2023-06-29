### CPU OpenGL

This is experimental software implementation of OpenGL, created as a learning exercise. The currently targeted version is 1.1, though many function are not yet implemented.

Currently working (more or less) features are:
```
- Triangle drawing using the basic glBegin / glEnd or by using version 1.1 buffers (drawArrays / drawElements)
- Pespective correct interpolation
- Texture filtering (nearest, bilinear)
- Blending
- Alpha testing
- Depth buffer functions
```

Some missing features include:
```
- Stencil operations
- Texture mipmapping
- Non 2D textures
- Drawing points / lines
- Lighting
```
### Usage

Interfacing is supported via GLX on X11 Linux and WGL on Windows. Implemented functions are the bare minimum to get GLUT and SDL applications working.

The library can be injected using [DLL redirection] on Windows, and using the LD_LIBRARY_PATH variable on Linux. However, due to missing unimplemented functions, the current usage is limited.

### Examples

As examples, some basic samples originally distributed by Silicon Graphics are included. These are available [here](https://www.opengl.org/archives/resources/code/samples/redbook/).

The current version is capable of running the [Yamagi Quake 2](https://github.com/yquake2/yquake2) sourceport.

![](https://github.com/ulmmat/CPU-OpenGL-Resources/blob/main/output.gif)

### Dependencies

[GLM](https://github.com/g-truc/glm) is used for math operations. SGI examples use the GLUT library.
