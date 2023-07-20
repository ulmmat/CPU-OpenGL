cmake_minimum_required(VERSION 3.14)

project(CPU_GL)

set(OGL_LIBRARY_NAME cpu_gl)
find_package(OpenMP REQUIRED)
set(USED_LIBS
    ${USED_LIBS}
    glm::glm
    ${OpenMP_CXX_LIB_NAMES}
)

set(COMPILE_OPTIONS
    ${COMPILE_OPTIONS}
    ${OpenMP_CXX_FLAGS}
)

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
    set(EXTRA_LIBS
        X11
    )
endif()


if (BUILD_DEBUG)
    set(COMPILE_DEFINITIONS
        ${COMPILE_DEFINITIONS}
    )
    if (DEBUG_DEF)
        set(COMPILE_DEFINITIONS
            ${COMPILE_DEFINITIONS}
            DEBUG
        )
    endif()
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
        -O3 -mavx -g -fopenmp
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
    src/ogl/ogl_stencil.cpp
    src/utility/time/Stopwatch.cpp
    src/utility/Random.cpp
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
target_link_libraries(cgl_lib ${USED_LIBS} ${EXTRA_LIBS})

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
        viewport
        varray
        fog
        stencil
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

if (BUILD_BENCHMARKS)
    set(AVAILABLE_BENCHMARKS
        texturing
        barycoords
    )

    foreach(ex ${AVAILABLE_BENCHMARKS})
        add_executable(${ex} benchmarks/${ex}.cpp)
        set_target_properties(${ex} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
        )
        target_compile_definitions(${ex} PRIVATE ${COMPILE_DEFINITIONS})
        target_compile_options(${ex} PRIVATE ${COMPILE_OPTIONS})
        target_link_libraries(${ex} cgl_lib)
        set_target_properties(${ex} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
            CXX_STANDARD 20
        )

    endforeach()
endif()


if (BUILD_TEST)
    set(CGL_TEST_SOURCE_FILES
    )
    # Fetch and compile googletest

    # set(INSTALL_GTEST OFF)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    ##################

    # Main testing executable
    add_executable(cgl_tests ${CGL_TEST_SOURCE_FILES})

    set_target_properties(cgl_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    )

    set_target_properties(cgl_tests PROPERTIES CXX_STANDARD 17)
    target_compile_options(cgl_tests PRIVATE ${PARACELL_CXX_COMPILE_OPTIONS})
    target_compile_definitions(cgl_tests PRIVATE ${PARACELL_COMPILE_DEFINITIONS})
    target_link_libraries(cgl_tests cgl_lib GTest::gtest_main)

    include(GoogleTest)

    gtest_discover_tests(cgl_tests)
endif()
