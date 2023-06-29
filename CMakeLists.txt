cmake_minimum_required(VERSION 3.14)

project(CPU_GL)

set(OGL_LIBRARY_NAME cpu_gl)

# Settings for Windows
if (WIN32)
    set(COMPILE_DEFINITIONS
        ${COMPILE_DEFINITIONS}
        WGL
    )
    # Used for shared libraries
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS  ON)
    set(OGL_LIBRARY_NAME opengl32)
endif()


# Settings for Linux
if (UNIX AND NOT APPLE)
    set(LINUX true)
    set(COMPILE_DEFINITIONS
        ${COMPILE_DEFINITIONS}
        GLX
    )
    set(OGL_LIBRARY_NAME GL)
    set(COMPILE_OPTIONS
        ${COMPILE_OPTIONS}
        -Wall
    )
endif()

if (BUILD_DEBUG)
    set(COMPILE_DEFINITIONS
        ${COMPILE_DEFINITIONS}
        DEBUG
    )
    set(COMPILE_OPTIONS
        ${COMPILE_OPTIONS}
        -O0 -g
    )
else()
    set(COMPILE_DEFINITIONS
        ${COMPILE_DEFINITIONS}
    )
    set(COMPILE_OPTIONS
        ${COMPILE_OPTIONS}
        -O3
    )
endif()

add_library(cgl_lib SHARED
    src/backends/glx/glx.cpp
    src/backends/glx/GLXConfig.cpp
    src/backends/wgl/wgl.cpp
    src/renderer/Renderer.cpp
    src/renderer/Rasterizer.cpp
    src/renderer/geometry/Line.cpp
    src/renderer/textures/Texture.cpp
    src/renderer/GenericBuffer.cpp
    src/renderer/framebuffer/FrameBuffer.cpp
    src/ogl/GLContext.cpp
    src/ogl/ogl_common.cpp
    src/ogl/ogl_begin.cpp
    src/ogl/ogl_alpha.cpp
    src/ogl/ogl_buffers.cpp
    src/ogl/ogl_shared.cpp
    src/ogl/ogl_textures.cpp
    src/ogl/ogl_unimplemented.cpp
    src/ogl/ogl_matrices.cpp
)
find_package(glm REQUIRED)
message(STATUS "hello ${GLM_BINARY_DIR} ${GLM_INCLUDE_DIRS}")

target_include_directories(cgl_lib PUBLIC "${CMAKE_BINARY_DIR}/src")
set_target_properties(cgl_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    CXX_STANDARD 20
)
target_compile_definitions(cgl_lib PRIVATE ${COMPILE_DEFINITIONS})
target_compile_options(cgl_lib PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(cgl_lib glm::glm)

set_target_properties(cgl_lib PROPERTIES OUTPUT_NAME ${OGL_LIBRARY_NAME})

if (BUILD_EXAMPLES)
    find_package(GLUT REQUIRED)
    set(AVAILABLE_EXAMPLES
        aapoly
        alpha
        hello
        smooth
        texbind
        texsub
        wrap
    )

    foreach(ex ${AVAILABLE_EXAMPLES})
        add_executable(${ex} examples/${ex}.cpp)
        set_target_properties(${ex} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
        )
        target_compile_definitions(${ex} PRIVATE ${COMPILE_DEFINITIONS})
        target_compile_options(${ex} PRIVATE ${COMPILE_OPTIONS})
        target_link_libraries(${ex} cgl_lib GLUT::GLUT)
        set_target_properties(${ex} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
            CXX_STANDARD 20
        )

    endforeach()

endif()


