#pragma once

#ifdef GLX

#include "dataStructures/vector.h"
#include "backends/glx/glx.h"

/**
 * Used to store some global X11 data, before creating an OpenGL context
 */
struct GLXConfig{
    void reset();

    /** Vector of available configs */
    cgl::Vector<GLXFBConfig> configs;
    /** Available visuals */
    XVisualInfo* config_vis_infos;

    /** Main "connection" to X server */
    Display* display = 0;
};

inline GLXConfig global_cfg;

#endif