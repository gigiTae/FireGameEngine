#pragma once

#include "ExportDefine.h"
#include <Windows.h>
#include "RendererModule/RendererHeader.h"

#define EDITOR_MODE

#ifdef EDITOR_MODE
#include "ToolModule/ToolModuleHeader.h"
#endif


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
			static LONG resizeHegiht;
			static LONG resizeWidth;
		private:
			const wchar_t* title = L"GameName";

			HINSTANCE hInstance= NULL;
			HWND hWnd =NULL;

			LONG screenWidth = 1920;
			LONG screenHeight = 1080;
			LONG screenLeft = 0;
			LONG screenTop = 0;

		 	RendererModule::D3DRenderer* rendererModule = nullptr;


#ifdef EDITOR_MODE
			ToolModule::IToolModule* toolModule = nullptr;
#endif // EDITOR_MODE

		};


	}
}

