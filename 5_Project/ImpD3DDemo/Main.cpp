#include "pch.h"
#include "Process.h"

// 버전 바꿀 때 신경써서 확인할 것
#pragma comment(lib, "../x64/Debug/ImpStructure.lib")
#pragma comment(lib, "../x64/Debug/ImpGraphicsEngine.lib")
//#pragma comment(lib, "../ImpLib/ImpGraphicsEngine.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::unique_ptr<Process> mainWindow = std::make_unique<Process>();

	mainWindow->Init(hInstance);
	mainWindow->Loop();

	return 0;
}