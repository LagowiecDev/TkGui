set(TKGUI_BACKEND_OPENGL ON)

if (TKGUI_BACKEND_OPENGL)
	add_subdirectory("OpenGL")
endif()

if (TKGUI_BACKEND_VULKAN)
	add_subdirectory("Vulkan")
endif()

if (TKGUI_BACKEND_DIRECTX)
	add_subdirectory("DirectX")
endif()