#include "EngineModulePCH.h"
#include "World.h"
#include "Entity.h"

ImpEngineModule::World::World()
	:m_lastEntityID(0) ,m_entities()
{

}

ImpEngineModule::World::~World()
{

}

ImpEngineModule::Entity* ImpEngineModule::World::CreateEntity()
{
	/// TODO : 나중에는 오브젝트 풀을 사용해서 관리한다.

	Entity* ent = new Entity(this, m_lastEntityID);
	++m_lastEntityID;
	m_entities.push_back(ent);

	return ent;
}

void ImpEngineModule::World::DestroyEntity(Entity* ent, bool immediate /*= false*/)
{
	if (ent == nullptr)
	{
		return; 
	}

	if (ent->m_state == Entity::EntityState::TO_BE_DESTROYED)
	{
		if (immediate)
		{
			m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), ent), m_entities.end());
			delete ent;
		}

		return;
	}

	ent->m_state = Entity::EntityState::TO_BE_DESTROYED;
	// TODO:: Destroy call back
	
	if (immediate)
	{
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), ent), m_entities.end());
		delete ent;
	}
}

void ImpEngineModule::World::DestroyEntity(size_t id, bool immediate /*= false*/)
{
	if (id > m_lastEntityID)
	{
		return;
	}

	Entity* ent = GetEntity(id);

	DestroyEntity(ent);
}

ImpEngineModule::Entity* ImpEngineModule::World::GetEntity(const std::string& name) const
{
	for (Entity* ent : m_entities)
	{
		if (name == ent->m_name)
		{
			return ent;
		}
	}
	return nullptr;
}

ImpEngineModule::Entity* ImpEngineModule::World::GetEntity(size_t id) const
{
	for (Entity* ent : m_entities)
	{
		if (id == ent->m_id)
		{
			return ent;
		}
	}
	return nullptr;
}

void ImpEngineModule::World::Reset()
{
	m_lastEntityID = 0;

	for (Entity* ent : m_entities)
	{
		ent->DestroyAllComponents();
		delete ent;
	}

	m_entities.clear();
}

void ImpEngineModule::World::Start()
{
	for (Entity* ent : m_entities)
	{
		ent->Start();
	}
}

void ImpEngineModule::World::Update()
{
	for (Entity* ent : m_entities)
	{
		ent->Update();
	}
}
