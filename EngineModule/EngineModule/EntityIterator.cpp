#include "EngineModulePCH.h"
#include "EntityIterator.h"
#include "World.h"

ImpEngineModule::EntityIterator::EntityIterator(ImpEngineModule::World* world,
	size_t index, bool isEnd, bool isIncludeToBeDestroyed)
	:m_world(world),m_index(index),m_isEnd(isEnd),
	m_isIncludeToBeDestroyed(isIncludeToBeDestroyed)
{
	if (m_index >= world->GetLastEntityID())
	{
		m_isEnd = true;
	}
}


ImpEngineModule::EntityIterator& ImpEngineModule::EntityIterator::operator++()
{
	++m_index;

	
	return *this;
}

ImpEngineModule::Entity* ImpEngineModule::EntityIterator::Get() const
{
	if (IsEnd())
		return nullptr;

	return m_world->GetEntity(m_index);
}

bool ImpEngineModule::EntityIterator::IsEnd() const
{
	return m_isEnd || m_index >= m_world->GetLastEntityID();
}

bool ImpEngineModule::EntityIterator::operator==(const EntityIterator& other)
{
	if (m_world != other.m_world)
	{
		return false;
	}

	
	

}
