#include "Engine.h"
#include <assert.h>

size_t Fire::EngineModule::Engine::resizeHegiht = 0;
size_t Fire::EngineModule::Engine::resizeWidth = 0;

void Fire::EngineModule::Engine::Initialize()
{
	InitializeWindow();

	/// 초기화 목록
	// ECS lib
	// RendererModule DLL
	// ToolModule lib


	Process();
}


void Fire::EngineModule::Engine::Uninitialize()
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void Fire::EngineModule::Engine::InitializeWindow()
{
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
		screenLeft+ screenWidth, screenTop+ screenHeight };

	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	hWnd = CreateWindow(title, title
		, WS_OVERLAPPEDWINDOW // 창이 겹침
		, screenLeft, screenTop, rect.right -rect.left, rect.bottom - rect.top
		, NULL, NULL, hInstance, NULL);

	assert(hWnd != 0 && "Failed To Start Game");

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
}

void Fire::EngineModule::Engine::Process()
{
	while (true)
	{

	}
}


//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	//	return true;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;
		Fire::EngineModule::Engine::resizeWidth = (UINT)LOWORD(lParam);
		Fire::EngineModule::Engine::resizeHegiht = (UINT)HIWORD(lParam);
		return 0;

	case WM_DPICHANGED:
		//if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
		//{
		//	//const int dpi = HIWORD(wParam);
		//	//printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
		//	const RECT* suggested_rect = (RECT*)lParam;
		//	::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
		//}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}