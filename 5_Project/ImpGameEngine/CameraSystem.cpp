#include "ImpGameEnginePCH.h"
#include "CameraSystem.h"

ImpGameEngine::CameraSystem::CameraSystem()
	:_cameraInfo{}, _engineModule(nullptr), _graphicsEngine(nullptr), _toolCamera(nullptr)
{}

ImpGameEngine::CameraSystem::~CameraSystem()
{

}

void ImpGameEngine::CameraSystem::Initialize(ImpGraphics::IImpGraphicsEngine* graphicsEngine, ImpEngineModule::EngineModule* engineModule)
{
	_graphicsEngine = graphicsEngine;
	_engineModule = engineModule;
}

void ImpGameEngine::CameraSystem::SetToolCamera(ImpEngineModule::Entity* main)
{
	_toolCamera = main;
}

const ImpGraphics::CameraInfo& ImpGameEngine::CameraSystem::GetCameraInfo()
{
	// Tool ī�޶� �ִ� ���
	if (_toolCamera)  
	{
		SetCameraInfo(_toolCamera);
	}
	else
	{
		ImpEngineModule::Entity* mainCamera = _engineModule->GetCameraManager()->GetMainCamera();
		
		assert(mainCamera && "����ī�޶� �������� �ʽ��ϴ�");
		SetCameraInfo(mainCamera);
	}

	return _cameraInfo;
}

void ImpGameEngine::CameraSystem::SetCameraInfo(ImpEngineModule::Entity* main)
{
	if (main == nullptr)
	{
		return;
	}

	ImpEngineModule::Camera* camera = main->GetComponent<ImpEngineModule::Camera>();
	ImpEngineModule::Transform* transform = main->GetComponent<ImpEngineModule::Transform>();

	if (camera == nullptr || transform == nullptr)
	{
		return;
	}

	_cameraInfo._nearPlain = camera->GetNearPlain();
	_cameraInfo._farPlain = camera->GerFarPlain();
	_cameraInfo._fieldOfView = camera->GetFieldOfView();
	_cameraInfo._isPerspective = camera->IsPerspective();
	_cameraInfo._position = transform->GetPosition();
	_cameraInfo._rotation = transform->GetRotation();
	_cameraInfo._scale = transform->GetScale();
}
