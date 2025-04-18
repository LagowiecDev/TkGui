#pragma once
#include "TkGui/TkGui_API.hpp"
#include "TkGui/TkGui_Types.hpp"

namespace TkGui
{
	static TkGuiDrawData s_drawData = { };
	static bool s_wasInitialized;

	TKGUI_API void Begin();
	TKGUI_API void Panel(Transform transform, BackgroundProperties background);
 	TKGUI_API void Text(Transform transform, TextProporties text);
	TKGUI_API void Label(Transform transform, BackgroundProperties background, TextProporties text);
	TKGUI_API bool Button(Transform transform, BackgroundProperties background, TextProporties text, ButtonProporties button);
	TKGUI_API void End();

	TKGUI_API TkGuiDrawData GetDrawData();
}