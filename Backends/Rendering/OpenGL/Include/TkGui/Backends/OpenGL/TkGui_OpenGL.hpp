#pragma once
#include "TkGui/Backends/OpenGL/TkGui_OpenGL_Backend_API.hpp"
#include <TkGui/TkGui.hpp>

namespace TkGui
{
    struct OpenGLGLObject
    {
        OpenGLGLObject();
        OpenGLGLObject(uint32_t vertexElementArray, uint32_t vertexElementBuffer, uint32_t indexElementBuffer, uint32_t textureBuffer, uint32_t indexCount);

        ~OpenGLGLObject();
    public:
        uint32_t VAO;
        uint32_t VBO;
        uint32_t EBO;
        uint32_t TBO;
        uint32_t IndexCount;
        //Face _face;
    };

    static Array<OpenGLGLObject> s_openGLDrawData;

	void TKGUI_BACKENDS_OPENGL_API InitOpenGL(void* proc);

    void TKGUI_BACKENDS_OPENGL_API BakeOpenGL(const DrawData& data);

	void TKGUI_BACKENDS_OPENGL_API DrawOpenGL(const DrawData& data);
    void TKGUI_BACKENDS_OPENGL_API DrawOpenGL();

	void TKGUI_BACKENDS_OPENGL_API TerminateOpenGL();
}