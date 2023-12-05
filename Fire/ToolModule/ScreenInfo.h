#pragma once
#include <windows.h>

namespace ToolModule
{
	namespace ScreenInfo
	{
		void LoadPosition(LONG& left, LONG& top);
		void LoadResoltuion(LONG& width, LONG& height);

		void SavePosition(LONG left, LONG top);
		void SaveResoltuion(LONG width, LONG height);
	};
}

