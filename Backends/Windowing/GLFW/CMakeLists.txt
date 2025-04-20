# (C) Copyright LagowiecDev 2025

# ─── PRINT INFO ────────────────────────────────────────────────
message(STATUS "")
message(STATUS "╔══════════════════════════════════════════════════════════════╗")
message(STATUS "║                TKGUI WINDOWING GLFW BACKEND                  ║")
message(STATUS "╚══════════════════════════════════════════════════════════════╝")
message(STATUS "")

set(TkGuiBackendsWindowingGLFWDIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(TkGuiBackendsWindowingGLFWHeaderDIR "${TkGuiBackendsWindowingGLFWDIR}/Include")
set(TkGuiBackendsWindowingGLFWSourceDIR "${TkGuiBackendsWindowingGLFWDIR}/Source")

file(GLOB_RECURSE TKGUI_BACKENDS_RENDERING_OPENGL_FILES_HEADERS "${TkGuiBackendsWindowingGLFWHeaderDIR}/*.hpp")
foreach(file IN LISTS TKGUI_BACKENDS_RENDERING_OPENGL_FILES_HEADERS)
    message(STATUS "Found header: ${file}")
endforeach()

file(GLOB_RECURSE TKGUI_BACKENDS_RENDERING_OPENGL_FILES_SOURCES "${TkGuiBackendsWindowingGLFWSourceDIR}/*.cpp")
foreach(file IN LISTS TKGUI_BACKENDS_RENDERING_OPENGL_FILES_SOURCES)
    message(STATUS "Found source: ${file}")
endforeach()

# Thats TkGuiMain
add_library(
    TkGuiBackendsWindowingGLFW
    STATIC
    ${TKGUI_BACKENDS_RENDERING_OPENGL_FILES_HEADERS}
    ${TKGUI_BACKENDS_RENDERING_OPENGL_FILES_SOURCES}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_target_properties(
        TkGuiBackendsWindowingGLFW
        PROPERTIES CXX_STANDARD 20
    )
endif()

generate_export_header(
    TkGuiBackendsWindowingGLFW
    BASE_NAME "TKGUI_BACKENDS_OPENGL"
    EXPORT_MACRO_NAME "TKGUI_BACKENDS_OPENGL_API"
    EXPORT_FILE_NAME "TkGui_Backends_OpenGL_Export.hpp"
    DEPRECATED_MACRO_NAME "TKGUI_BACKENDS_OPENGL_DEPRECATED"
    NO_EXPORT_MACRO_NAME "TKGUI_BACKENDS_OPENGL_API_NONE"
    NO_DEPRECATED_MACRO_NAME "TKGUI_BACKENDS_OPENGL_SUPPORTED"
)

target_include_directories(TkGuiBackendsWindowingGLFW PUBLIC "${TkGuiBackendsWindowingGLFWHeaderDIR}" "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(TkGuiBackendsWindowingGLFW PRIVATE TkGui)