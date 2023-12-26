#include "EngineModulePCH.h"
#include "CameraManager.h"
#include "World.h"
#include "Camera.h"
#include "Transform.h"

ImpEngineModule::CameraManager::CameraManager()
	:_world(nullptr),_mainCamera(nullptr)
{}

ImpEngineModule::CameraManager::~CameraManager()
{

}

void ImpEngineModule::CameraManager::Initialize(World* world)
{
	_world = world;

	_mainCamera = FindMainCamera();
}

void ImpEngineModule::CameraManager::Update()
{
	_mainCamera = FindMainCamera();
}

void ImpEngineModule::CameraManager::Finalize()
{

}

ImpEngineModule::Entity* ImpEngineModule::CameraManager::FindMainCamera()
{
	for (Entity* ent : _world->Each<Transform, Camera>(false))
	{
		if (ent->GetComponent<Camera>()->IsMain())
		{
			return ent;
		}
	}

	return nullptr;
}

ImpEngineModule::Entity* ImpEngineModule::CameraManager::GetMainCamera()
{
	return _mainCamera;
}
