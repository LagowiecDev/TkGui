#pragma once
#include "TkGui/Backends/OpenGL/TkGui_OpenGL_Backend_API.hpp"
#include <TkGui/TkGui.hpp>

namespace TkGui
{
	void TKGUI_BACKEND_OPENGL_API InitOpenGL(text_t version);

	void TKGUI_BACKEND_OPENGL_API DrawOpenGL(const DrawData& data);

	void TKGUI_BACKEND_OPENGL_API TerminateOpenGL();
}