#include "ImpGameEnginePCH.h"
#include "WindowInfomation.h"

#ifdef IMP_EDITOR_MODE
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

LONG ImpGameEngine::WindowInfomation::resizeWidth = 0;
LONG ImpGameEngine::WindowInfomation::resizeHegiht = 0;

LRESULT CALLBACK ImpGameEngine::WindowInfomation::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef IMP_EDITOR_MODE
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
#endif

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

#ifdef IMP_EDITOR_MODE
	case WM_MOVE:
	{

	}
	break;
#endif // EDITOR_MODE

	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;
		{
			resizeWidth = LOWORD(lParam);
			resizeHegiht = HIWORD(lParam);

		}
		break;

#ifdef IMP_EDITOR_MODE
	case WM_DPICHANGED:
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
		{
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
