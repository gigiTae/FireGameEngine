#include "EngineModulePCH.h"
#include "World.h"
#include "Entity.h"

ImpEngineModule::World::World()
	:_lastEntityID(0) ,_entities()
{

}

ImpEngineModule::World::~World()
{

}

ImpEngineModule::Entity* ImpEngineModule::World::CreateEntity()
{
	/// TODO : 나중에는 오브젝트 풀을 사용해서 관리한다.
	++_lastEntityID;
	Entity* ent = new Entity(this, _lastEntityID);

	_entities.push_back(ent);

	return ent;
}

void ImpEngineModule::World::DestroyEntity(Entity* ent, bool immediate /*= false*/)
{
	if (ent == nullptr)
	{
		return; 
	}

	if (ent->_state == Entity::EntityState::ToBeDestroyed)
	{
		if (immediate)
		{
			_entities.erase(std::remove(_entities.begin(), _entities.end(), ent), _entities.end());
			delete ent;
		}

		return;
	}

	ent->_state = Entity::EntityState::ToBeDestroyed;
	// TODO:: Destroy call back
	
	if (immediate)
	{
		_entities.erase(std::remove(_entities.begin(), _entities.end(), ent), _entities.end());
		delete ent;
	}
}

void ImpEngineModule::World::DestroyEntity(size_t id, bool immediate /*= false*/)
{
	if (id >= _lastEntityID)
	{
		return;
	}

	Entity* ent = GetEntity(id);

	DestroyEntity(ent);
}

ImpEngineModule::Entity* ImpEngineModule::World::GetEntity(const std::string& name) const
{
	for (Entity* ent : _entities)
	{
		if (name == ent->_name)
		{
			return ent;
		}
	}
	return nullptr;
}

ImpEngineModule::Entity* ImpEngineModule::World::GetEntity(size_t id) const
{
	for (Entity* ent : _entities)
	{
		if (id == ent->_id)
		{
			return ent;
		}
	}
	return nullptr;
}

void ImpEngineModule::World::Reset()
{
	_lastEntityID = 0;

	for (Entity* ent : _entities)
	{
		ent->DestroyAllComponents();
		delete ent;
	}

	_entities.clear();
}

void ImpEngineModule::World::Start()
{
	for (Entity* ent : _entities)
	{
		ent->Start();
	}
}

void ImpEngineModule::World::Update(float dt)
{
	for (Entity* ent : _entities)
	{
		ent->Update(dt);
	}
}
