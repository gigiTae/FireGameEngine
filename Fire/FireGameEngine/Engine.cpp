#include "FireGameEnginepch.h"
#include "Engine.h"
#include "RenderingSystem.h"

LONG Fire::EngineModule::Engine::resizeHegiht = 0;
LONG Fire::EngineModule::Engine::resizeWidth = 0;

#ifdef EDITOR_MODE
LONG Fire::EngineModule::Engine::newScreenLeft = 0;
LONG Fire::EngineModule::Engine::newScreenTop = 0;
#endif

void Fire::EngineModule::Engine::Initialize()
{
	InitializeWindow();

	/// 초기화 목록
	world = new Fire::ECS::World();

	// RendererModule 
	rendererModule = new RendererModule::D3DRenderer();
	rendererModule->Initialize(hWnd, screenWidth, screenHeight);

#ifdef EDITOR_MODE
	toolModule = new ToolModule::FireEditor();
	toolModule->Initialize(hWnd,
		rendererModule->GetDevice(), rendererModule->GetDeviceContext());
#endif 

	renderingSystem = new Fire::ECS::RenderingSystem(rendererModule);

	world->RegisterSystem(renderingSystem);
}


void Fire::EngineModule::Engine::Uninitialize()
{
	delete renderingSystem;

	delete world;

#ifdef EDITOR_MODE
	toolModule->Finalize();
	delete toolModule;
#endif

	rendererModule->Finalize();
	delete rendererModule;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void Fire::EngineModule::Engine::InitializeWindow()
{
#ifdef EDITOR_MODE
	ToolModule::ScreenInfo::LoadPosition(screenLeft, screenTop);
	ToolModule::ScreenInfo::LoadResoltuion(screenWidth, screenHeight);
#endif // EDITOR_MODE667

	hInstance = static_cast<HINSTANCE>(GetModuleHandle(NULL));

	WNDCLASS wndClass{};

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = title;

	RegisterClass(&wndClass);

	RECT rect{ screenLeft, screenTop,
		screenLeft + screenWidth, screenTop + screenHeight };

	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	screenTop = rect.top;
	screenLeft = rect.left;
	screenWidth = rect.right - rect.left;
	screenHeight = rect.bottom - rect.top;

	hWnd = CreateWindow(title, title
		, WS_OVERLAPPEDWINDOW // 창이 겹침
		, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top
		, NULL, NULL, hInstance, NULL);

	assert(hWnd != 0 && "Failed To Start Game");

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
}

void Fire::EngineModule::Engine::Process()
{
	MSG msg;
	bool isDone = false;

	while (!isDone)
	{
		// 픽메세지 함수를 사용해서 메세지를 관리한다.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				isDone = true;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (resizeWidth != 0 && resizeHegiht != 0)
			{
				rendererModule->OnResize(resizeWidth, resizeHegiht);

				resizeHegiht = 0;
				resizeWidth = 0;
			}


#ifdef EDITOR_MODE
			toolModule->NewFrame();
			toolModule->Load(world);
#endif
			rendererModule->BeginRender();
			rendererModule->Render();

			world->Tick(0.1f);

#ifdef EDITOR_MODE
			toolModule->EndRender();
#endif

			rendererModule->EndRender();
		}

	}

}

#ifdef EDITOR_MODE
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef EDITOR_MODE
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
#endif

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

#ifdef EDITOR_MODE
	case WM_MOVE:
	{
		int left = (int)(short)LOWORD(lParam);
		int top = (int)(short)HIWORD(lParam);

		ToolModule::ScreenInfo::SavePosition(static_cast<LONG>(left),
			static_cast<LONG>(top));
	}
	break;
#endif // EDITOR_MODE

	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;
		{
			Fire::EngineModule::Engine::resizeWidth = (UINT)LOWORD(lParam);
			Fire::EngineModule::Engine::resizeHegiht = (UINT)HIWORD(lParam);

			ToolModule::ScreenInfo::SaveResoltuion(Fire::EngineModule::Engine::resizeWidth
				, Fire::EngineModule::Engine::resizeHegiht);
		}
		break;

#ifdef EDITOR_MODE
	case WM_DPICHANGED:
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
		{
			//const int dpi = HIWORD(wParam);
			//printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
			const RECT* suggested_rect = (RECT*)lParam;
			::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		break;
#endif 

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}