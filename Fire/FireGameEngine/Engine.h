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
			Engine() =default;
			~Engine() =default;

		public:
			void Initialize();
			void Uninitialize();
			void Process();

		private:
			void InitializeWindow();

		public:
			static size_t resizeHegiht;
			static size_t resizeWidth;
		private:
			const wchar_t* title = L"GameName";

			HINSTANCE hInstance;
			HWND hWnd;

			size_t screenWidth = 1920;
			size_t screenHeight = 1080;
			size_t screenLeft = 0;
			size_t screenTop = 0;
		};


	}
}

