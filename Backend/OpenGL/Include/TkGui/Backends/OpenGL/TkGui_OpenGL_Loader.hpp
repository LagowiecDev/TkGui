#pragma once

#define TKGUI_BACKEND_OPENGL_LOADER_GLAD 0b0001
#define TKGUI_BACKEND_OPENGL_LOADER_GL3W 0b0010

#define TKGUI_BACKEND_OPENGL_LOADER TKGUI_BACKEND_OPENGL_LOADER_GL3W

#if TKGUI_BACKEND_OPENGL_LOADER == TKGUI_BACKEND_OPENGL_LOADER_GLAD
#include "TkGui/Backends/OpenGL/TkGui_OpenGL_Loader_Glad.hpp"
#define OpenGLLoader_Init() gladLoaderLoadGL()
#define OpenGLLoader_Init_Loader(proc) gladLoadGL(reinterpret_cast<GLADloadfunc>(proc))
#define OpenGLLoadFailed(load) !load
#endif

#if TKGUI_BACKEND_OPENGL_LOADER == TKGUI_BACKEND_OPENGL_LOADER_GL3W
#include "TkGui/Backends/OpenGL/TkGui_OpenGL_Loader_Gl3w.hpp"
#define OpenGLLoader_Init() gl3wInit()
#define OpenGLLoader_Init_Loader(proc) gl3wInit2(reinterpret_cast<GL3WGetProcAddressProc>(proc))
#define OpenGLLoadFailed(load) load
#endif