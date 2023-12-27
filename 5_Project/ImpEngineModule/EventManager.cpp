#include "EngineModulePCH.h"
#include "EventManager.h"

ImpEngineModule::EventManager::EventManager()
	:_world(nullptr)
{

}

ImpEngineModule::EventManager::~EventManager()
{}

void ImpEngineModule::EventManager::Initialize(World* world)
{
	_world = world;
}


void ImpEngineModule::EventManager::Finalize()
{

}

void ImpEngineModule::EventManager::Update()
{

}

void ImpEngineModule::EventManager::UnSubScribeAll(void* subscriber)
{

}
