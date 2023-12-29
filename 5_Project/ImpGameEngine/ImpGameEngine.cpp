#include "ImpGameEnginePCH.h"
#include "ImpGameEngine.h"
#include "CameraSystem.h"
#include "RenderingSystem.h"

#pragma comment(lib, "../ImpLib/ImpGraphicsEngine.lib")
#include "../ImpGraphicsEngine/IImpGraphicsEngine.h"

ImpGameEngine::ImpGameEngine::ImpGameEngine()
	:_graphicsEngine(nullptr), _engineModule(nullptr),_cameraSystem(nullptr)
	,_renderingSystem(nullptr)
{
}

ImpGameEngine::ImpGameEngine::~ImpGameEngine()
{}

void ImpGameEngine::ImpGameEngine::Initialize(WindowInfomation info)
{
	_graphicsEngine = ImpGraphics::EngineExporter::GetEngine();

	_engineModule = new ImpEngineModule::EngineModule();
	_cameraSystem = new CameraSystem();
	_renderingSystem = new RenderingSystem();

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
	_renderingSystem->Initialize(_graphicsEngine, _engineModule);

	// 5. 게임루프 시작
	_engineModule->Start();
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

			_renderingSystem->Update();

			_graphicsEngine->Update(dt);

			_graphicsEngine->SetCamera(_cameraSystem->GetCameraInfo());
			_graphicsEngine->BeginRender();
			_graphicsEngine->Render(ImpGraphics::IImpGraphicsEngine::RendererType::Forward);

			_graphicsEngine->EndRender();
		}

	}
}

void ImpGameEngine::ImpGameEngine::Finalize()
{
	_renderingSystem->Finalize();

	_engineModule->Finalize();
	_graphicsEngine->Finalize();

	// 메모리 해제

	ImpGraphics::EngineExporter::DeleteEngine();

	delete _engineModule;
	delete _cameraSystem;
	delete _renderingSystem;
}

