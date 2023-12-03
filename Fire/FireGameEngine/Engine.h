#pragma once

#include "ExportDefine.h"
#include <Windows.h>

namespace Fire
{
	namespace EngineModule
	{
		class FIRE_ENGNIE_API Engine
		{
		public:
			Engine() = default;
			~Engine() =default;

		public:
			void Initialize();
			void Uninitialize();

		private:
			void InitializeWindow();
		
		private:
			const wchar_t* title = L"GameName";

			/// WINDOW
			HINSTANCE hInstance;
			HWND hWnd;

			size_t screenWidth = 1920;
			size_t screenHeight = 1080;
			size_t screenLeft = 0;
			size_t screenTop = 0;

		};


	}
}

