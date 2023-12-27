#include "EngineModulePCH.h"
#include "EngineModule.h"
#include "World.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "CameraManager.h"

ImpEngineModule::EngineModule::EngineModule()
{
	_world = std::make_unique<World>();

	_eventManager = std::make_unique<EventManager>();
	_resourceManager = std::make_unique<ResourceManager>();
	_inputManager = std::make_unique<InputManager>();

	_timeManager = std::make_unique<TimeManager>();
	_worldManager = std::make_unique<WorldManager>();
	_cameraManager = std::make_unique<CameraManager>();
}

ImpEngineModule::EngineModule::~EngineModule()
{

}

void ImpEngineModule::EngineModule::Initialize(HWND hWnd, std::wstring startWorld)
{
	_world->Initialize(_eventManager.get(), _inputManager.get(), _resourceManager.get());

	_timeManager->Initialize();
	_inputManager->Initalize(hWnd);
	_resourceManager->Initailize(startWorld);
	_worldManager->Initialize(startWorld, _world.get(), _resourceManager.get());
	_eventManager->Initialize(_world.get());
	_worldManager->LoadWorld();

	// 메인 카메라 설정
	_cameraManager->Initialize(_world.get());
		
	_world->Start();
}

float ImpEngineModule::EngineModule::Update()
{
	float dt = _timeManager->Update();
	_inputManager->Update();

	_world->Update(dt);
	
	// 이벤트 처리
	_eventManager->Update();

	return dt;
}

void ImpEngineModule::EngineModule::Finalize()
{
	_eventManager->Finalize();
	_timeManager->Finalize();
	_resourceManager->Finalize();
	_inputManager->Finalize();
	_worldManager->Finalize();
	_world->Reset();
}
