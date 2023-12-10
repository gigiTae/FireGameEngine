#pragma once


namespace Fire
{
	namespace ECS
	{
		class RenderingSystem;
	}

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
			Fire::ECS::World* world = nullptr;
			Fire::ECS::RenderingSystem* renderingSystem = nullptr;

#ifdef EDITOR_MODE
		private:
			ToolModule::IToolModule* toolModule = nullptr;

		public:
			static LONG newScreenLeft;
			static LONG newScreenTop;
#endif // EDITOR_MODE

		};


	}
}

