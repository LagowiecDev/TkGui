cmake_minimum_required(VERSION 3.12)
project(TkGui VERSION 1.0 LANGUAGES CXX)

include(GenerateExportHeader)

# ─── PRINT INFO ────────────────────────────────────────────────
message(STATUS "")
message(STATUS "╔══════════════════════════════════════════════════════════════╗")
message(STATUS "║                            TKGUI                             ║")
message(STATUS "║               (C) Copyright LagowiecDev 2025                 ║")
message(STATUS "║                 Developed by LagowiecDev                     ║")
message(STATUS "╚══════════════════════════════════════════════════════════════╝")
message(STATUS "")

# ─── OPTIONS ───────────────────────────────────────────────────
set(TKGUI_BACKENDS ON "Enable TkGui backends")
set(TKGUI_TESTS ON "Enable TkGui tests")

set(TKGUI_VERSION_MAJOR 0)
set(TKGUI_VERSION_MINOR 0)
set(TKGUI_VERSION_PATCH 0)
set(TKGUI_VERSION_HOTFIX 0)
set(TKGUI_VERSION "${TKGUI_VERSION_MAJOR}.${TKGUI_VERSION_MINOR}.${TKGUI_VERSION_PATCH}.${TKGUI_VERSION_HOTFIX}")
set(TKGUI_DEVELOPER "LagowiecDev, TkGui Contributors")

message(STATUS "TKGUI_BACKENDS: ${TKGUI_BACKENDS}")
message(STATUS "TKGUI_TESTS: ${TKGUI_TESTS}")

# ─── LIBRARY TYPE ──────────────────────────────────────────────
if (NOT DEFINED TKGUI_LIBRARY_TYPE)
    if (BUILD_SHARED_LIBS)
        set(TKGUI_LIBRARY_TYPE SHARED)
    else()
        set(TKGUI_LIBRARY_TYPE STATIC)
    endif()
endif()

# ─── DIRECTORIES ───────────────────────────────────────────────
set(TkGuiDir "${CMAKE_CURRENT_SOURCE_DIR}")
set(TkGuiBuildDir "${CMAKE_CURRENT_BINARY_DIR}")
set(TkGuiHeaderDir "${TkGuiDir}/Include")
set(TkGuiSourceDir "${TkGuiDir}/Source")

# ─── FILES ──────────────────────────────────────────────────────
file(GLOB_RECURSE TkGuiFilesHeaders "${TkGuiHeaderDir}/*.hpp")
file(GLOB_RECURSE TkGuiFilesSources "${TkGuiSourceDir}/*.cpp")

foreach(file IN LISTS TkGuiFilesHeaders)
    message(STATUS "Found header: ${file}")
endforeach()

foreach(file IN LISTS TkGuiFilesSources)
    message(STATUS "Found source: ${file}")
endforeach()

# ─── LIBRARY ────────────────────────────────────────────────────
add_library(TkGui ${TKGUI_LIBRARY_TYPE} ${TkGuiFilesHeaders} ${TkGuiFilesSources})

if (WIN32)
    configure_file("${TkGuiDir}/MetaInfo/TkGui.rc.in" "${TkGuiBuildDir}/TkGui.rc" @ONLY)
    target_sources(TkGui PRIVATE "${TkGuiBuildDir}/TkGui.rc")
endif()

set_target_properties(
    TkGui
    PROPERTIES
    CXX_STANDARD 20
    POSITION_INDEPENDENT_CODE ON
)

# ─── EXPORT MACROS ─────────────────────────────────────────────
generate_export_header(
    TkGui
    BASE_NAME "TKGUI"
    EXPORT_MACRO_NAME "TKGUI_API"
    EXPORT_FILE_NAME "TkGui_Export.hpp"
    DEPRECATED_MACRO_NAME "TKGUI_DEPRECATED"
    NO_EXPORT_MACRO_NAME "TKGUI_API_NONE"
    NO_DEPRECATED_MACRO_NAME "TKGUI_SUPPORTED"
)

# ─── INCLUDE PATHS ─────────────────────────────────────────────
target_include_directories(TkGui PUBLIC
    "${TkGuiHeaderDir}"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

# ─── SUBDIRECTORIES ────────────────────────────────────────────
if (TKGUI_BACKENDS)
    add_subdirectory("Backend")
endif()

# TODO: Combine TkGui with TkGuiBackend as TkGuiPlatform