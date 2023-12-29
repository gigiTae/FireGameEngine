#include "pch.h"
#include "Application.h"
#include "../ImpGameEngine/IImpEngine.h"

Application::Application()
	:_gameEngine{}, _info()
{


}

Application::~Application()
{
}

void Application::Initialize(HINSTANCE hInstance)
{
	// ToolEngine 시작
	_gameEngine = ImpGameEngine::EngineExporter::GetToolEngine();
	
	// GameEngine 시작
	//_gameEngine = ImpGameEngine::EngineExporter::GetGameEngine();


	_info._hInstance = hInstance;

	// Window 초기화
	InitializeWindow(hInstance);

	_gameEngine->Initialize(_info);
}

void Application::Process()
{
	_gameEngine->Process();
}

void Application::Finalize()
{
	_gameEngine->Finalize();

	ImpGameEngine::EngineExporter::DeleteEngine();
}


void Application::InitializeWindow(HINSTANCE hInstance)
{
	WNDCLASS wndClass{};

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = ImpGameEngine::WindowInfomation::WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = _info._title;

	RegisterClass(&wndClass);

	RECT rect{ _info._screenLeft, _info._screenTop,
		_info._screenLeft + _info._screenWidth, _info._screenTop + _info._screenHeight };

	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	_info._screenTop = rect.top;
	_info._screenLeft = rect.left;
	_info._screenWidth = rect.right - rect.left;
	_info._screenHeight = rect.bottom - rect.top;

	_info._hWnd = CreateWindow(_info._title, _info._title
		, WS_OVERLAPPEDWINDOW // 창이 겹침
		, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top
		, NULL, NULL, hInstance, NULL);

	ShowWindow(_info._hWnd, SW_SHOWNORMAL);
	UpdateWindow(_info._hWnd);
}
