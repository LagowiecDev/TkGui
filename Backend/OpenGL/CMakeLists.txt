# (C) Copyright LagowiecDev 2025

set(TkGuiDIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(TkGuiBackendHeaderDIR "${TkGuiDIR}/Include")
set(TkGuiBackendSourceDIR "${TkGuiDIR}/Source")

file(GLOB_RECURSE TKGUI_BACKEND_FILES_HEADERS "${TkGuiBackendHeaderDIR}/*.hpp")
foreach(file IN LISTS TKGUI_FILES_HEADERS)
    message(STATUS "Found header: ${file}")
endforeach()

file(GLOB_RECURSE TKGUI_BACKEND_FILES_SOURCES "${TkGuiBackendSourceDIR}/*.cpp")
foreach(file IN LISTS TKGUI_FILES_SOURCES)
    message(STATUS "Found source: ${file}")
endforeach()

# Thats TkGuiMain
add_library(
    TkGuiBackend
    STATIC
    #${TKGUI_BACKEND_FILES_HEADERS}
    ${TKGUI_BACKEND_FILES_SOURCES}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_target_properties(
        TkGuiBackend
        PROPERTIES CXX_STANDARD 20
    )
endif()

generate_export_header(
    TkGuiBackend
    BASE_NAME "TKGUI_BACKEND_OPENGL"
    EXPORT_MACRO_NAME "TKGUI_BACKEND_OPENGL_API"
    EXPORT_FILE_NAME "TkGui_Backend_OpenGL_Export.hpp"
    DEPRECATED_MACRO_NAME "TKGUI_BACKEND_OPENGL_DEPRECATED"
    NO_EXPORT_MACRO_NAME "TKGUI_BACKEND_OPENGL_API_NONE"
    NO_DEPRECATED_MACRO_NAME "TKGUI_BACKEND_OPENGL_SUPPORTED"
)

target_include_directories(TkGuiBackend PUBLIC "${TkGuiBackendHeaderDIR}" "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(TkGuiBackend PRIVATE TkGui)