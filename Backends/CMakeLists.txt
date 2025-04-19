# ─── PRINT INFO ────────────────────────────────────────────────
message(STATUS "")
message(STATUS "╔══════════════════════════════════════════════════════════════╗")
message(STATUS "║                                                              ║")
message(STATUS "║                       TKGUI BACKENDS                         ║")
message(STATUS "║                                                              ║")
message(STATUS "╚══════════════════════════════════════════════════════════════╝")
message(STATUS "")

if (TKGUI_BACKENDS_RENDERING)
	add_subdirectory("Rendering")
endif()