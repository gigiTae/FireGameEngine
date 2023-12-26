#include "ImpGameEnginePCH.h"
#include "ImpGameEngine.h"
#include "CameraSystem.h"

#pragma comment(lib, "../ImpLib/ImpGraphicsEngine.lib")
#include "../ImpGraphicsEngine/ImpGraphicsEngine.h"

ImpGameEngine::ImpGameEngine::ImpGameEngine()
	:_graphicsEngine(nullptr), _engineModule(nullptr),_cameraSystem(nullptr)
#ifdef IMP_EDITOR_MODE
	, _editor(nullptr)
#endif
{
}

ImpGameEngine::ImpGameEngine::~ImpGameEngine()
{}

void ImpGameEngine::ImpGameEngine::Initialize(WindowInfomation info)
{
	_graphicsEngine = new ImpGraphics::ImpGraphicsEngine();
	_engineModule = new ImpEngineModule::EngineModule();
	_cameraSystem = new CameraSystem();

	// 1. 그래픽스 엔진 초기화 
#pragma warning(disable : 4311)
#pragma warning(disable : 4302)
	_graphicsEngine->Initialize(reinterpret_cast<int>(info._hInstance), reinterpret_cast<int>(info._hWnd),
		info._screenWidth, info._screenHeight);
#pragma warning(default : 4311)
#pragma warning(default : 4302)

	// 2. 시작 월드 지정
	const std::wstring startWorld = L"Default";

	// 3. EngineModule 초기화
	_engineModule->Initialize(info._hWnd, startWorld);

	// 4. System 초기화
	_cameraSystem->Initialize(_graphicsEngine,_engineModule);

#ifdef IMP_EDITOR_MODE
	_editor = new ImpToolModule::ImpEditor();
	_editor->Initialize(info._hWnd, _graphicsEngine->GetDevice(),
		_graphicsEngine->GetDeviceContext(), _engineModule);

	_cameraSystem->SetToolCamera(_editor->GetToolCamera()); 
#endif 
}

void ImpGameEngine::ImpGameEngine::Process()
{
	MSG msg;

	bool isDone = false;
	while (!isDone)
	{
		// 1. Window Message
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
			// ResizeWindow
			if (WindowInfomation::resizeHegiht != 0 && WindowInfomation::resizeWidth != 0)
			{
				_graphicsEngine->SetClientSize(WindowInfomation::resizeWidth, WindowInfomation::resizeHegiht);

				WindowInfomation::resizeHegiht = 0;
				WindowInfomation::resizeWidth = 0;
			}

			float dt = _engineModule->Update();			
			_graphicsEngine->Update(dt);

#ifdef IMP_EDITOR_MODE
			_editor->NewFrame();
			_editor->Update();
#endif // IMP_EDITOR_MODE

			_graphicsEngine->SetCamera(_cameraSystem->GetCameraInfo());
			_graphicsEngine->BeginRender();
			_graphicsEngine->Render(ImpGraphics::IImpGraphicsEngine::RendererType::Forward);
			   
#ifdef IMP_EDITOR_MODE
			_editor->EndRender(); 
#endif // IMP_EDITOR_MODE

			_graphicsEngine->EndRender();
		}

	}
}

void ImpGameEngine::ImpGameEngine::Finalize()
{
	_engineModule->Finalize();
	_graphicsEngine->Finalize();

#ifdef IMP_EDITOR_MODE
	_editor->Finalize();
	delete _editor;
#endif // IMP_EDITOR_MODE

	// 메모리 해제
	delete _graphicsEngine;
	delete _engineModule;
	delete _cameraSystem;
}

