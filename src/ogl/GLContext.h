#pragma once

#include "dataStructures/set.h"
#include "ogl/ogl_types.h"
#include "renderer/Renderer.h"

#ifdef GLX
#include <X11/Xutil.h>
#endif

#ifdef WGL
#include "backends/wgl/wgl.h"
#endif

namespace cgl
{

/**
 * @brief Class used to represent a created OpenGL context
 *
 * Implementation differs between platforms. The main function is for flushing the framebuffer,
 * and access to the renderer for drawing.
 */
class GLContext{
    public:
        ~GLContext();

        /**
         * Used renderer, which holds the underlying framebuffers
         */
        Renderer renderer;

        // Copies data over from the framebuffer to the window
        void flushFramebuffer();

        int width;
        int height;

// If the backend is X11
#ifdef GLX

        void createImage(Display* display, Visual* vis, int depth, int width, int height);
        XImage* getDrawImage() const;
        XImage* getReadImage() const;
        Display* display = nullptr;
        GC gc = nullptr;

        /**
         * @brief An XImage is created for each framebuffer
         *
         * An XImage is used to transform data to the window
         */
        Map<GLenum, XImage*> backend_images;

        /**
         * ID on the main buffer into which is output is drawn
         *
         * Expected to be an ID of an XWindow instance
         */
        XID draw_buffer;
    private:
        void clearImages();
#endif

// If the backend is WGL
#ifdef WGL
        // Data created for each Framebuffer
        struct FramebufferDIB{
            /**
             * An extra DC is created which handles a custom bitmap which is used to blit
             * data to the main window
             */
            HDC extra_handle;

            /**
             * A bitmap is used to copy over data from the framebuffer and then copied over to the main window
             *
             * This extra layer of copy indirection is not ideal, though the performance impact is still irrelevant
             */
            HBITMAP dib_bitmap;
            char* dib_data;
            const FrameBuffer* fb;
        };

        FramebufferDIB createDIB(const FrameBuffer* framebuffer, int width, int height);

        const FramebufferDIB* getDrawDIB() const;
        void clearDIBs();
        void setHandle(HDC handle);

        HDC device_handle = 0;
    private:
        void resizeDIBs(int width, int height);

        Map<GLenum, FramebufferDIB> framebuffer_dibs;
#endif



};

/**
 * Globally stored all created OpenGL contexts
 */
inline Set<GLContext*> contexts;
/**
 * Context from contexts that is currently set as current
 */
inline GLContext* cur_context = nullptr;

}
