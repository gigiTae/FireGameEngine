#include "EngineModulePCH.h"
#include "EventManager.h"

ImpEngineModule::EventManager::EventManager():_eventQueue{}
{

}

ImpEngineModule::EventManager::~EventManager()
{}

void ImpEngineModule::EventManager::Initialize()
{

}

void ImpEngineModule::EventManager::Finalize()
{
	_eventQueue.clear();
}

void ImpEngineModule::EventManager::Update()
{
	// �̺�Ʈ ť�� ���� �Լ����� ȣ���Ѵ�.
	for (Event& event : _eventQueue)
	{
		event.function();
	}

	_eventQueue.clear();
}

void ImpEngineModule::EventManager::PushBackEvent(const Event& event)
{
	_eventQueue.push_back(event);
}

