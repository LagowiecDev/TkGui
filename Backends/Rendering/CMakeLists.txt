# ─── PRINT INFO ────────────────────────────────────────────────
message(STATUS "")
message(STATUS "╔══════════════════════════════════════════════════════════════╗")
message(STATUS "║                       TKGUI RENDERING                        ║")
message(STATUS "║                          BACKENDS                            ║")
message(STATUS "╚══════════════════════════════════════════════════════════════╝")
message(STATUS "")

if (TKGUI_BACKENDS_RENDERING_OPENGL)
	add_subdirectory("OpenGL")
endif()

if (TKGUI_BACKENDS_RENDERING_VULKAN)
	add_subdirectory("Vulkan")
endif()

if (TKGUI_BACKENDS_RENDERING_DIRECTX)
	add_subdirectory("DirectX")
endif()