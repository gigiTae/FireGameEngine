#include "EngineModulePCH.h"
#include "World.h"
#include "Entity.h"

EngineModule::World::World()
	:lastEntityID(0) ,entities()
{

}

EngineModule::World::~World()
{

}

EngineModule::Entity* EngineModule::World::CreateEntity()
{
	/// TODO : 나중에는 오브젝트 풀을 사용해서 관리한다.

	Entity* ent = new Entity(this, lastEntityID);
	++lastEntityID;
	entities.push_back(ent);

	return ent;
}

void EngineModule::World::DestroyEntity(Entity* ent, bool immediate /*= false*/)
{
	if (ent == nullptr)
	{
		return; 
	}

	if (ent->state == Entity::EntityState::TO_BE_DESTROYED)
	{
		if (immediate)
		{
			entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
			delete ent;
		}

		return;
	}

	ent->state = Entity::EntityState::TO_BE_DESTROYED;
	// TODO:: Destroy call back
	
	if (immediate)
	{
		entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
		delete ent;
	}
}

void EngineModule::World::DestroyEntity(size_t id, bool immediate /*= false*/)
{
	if (id > lastEntityID)
	{
		return;
	}

	Entity* ent = GetEntity(id);

	DestroyEntity(ent);
}

EngineModule::Entity* EngineModule::World::GetEntity(const std::string& name) const
{
	for (Entity* ent : entities)
	{
		if (name == ent->name)
		{
			return ent;
		}
	}
	return nullptr;
}

EngineModule::Entity* EngineModule::World::GetEntity(size_t id) const
{
	for (Entity* ent : entities)
	{
		if (id == ent->id)
		{
			return ent;
		}
	}
	return nullptr;
}

void EngineModule::World::Reset()
{
	lastEntityID = 0;

	for (Entity* ent : entities)
	{
		ent->DestroyAllComponents();
		delete ent;
	}

	entities.clear();
}

void EngineModule::World::Start()
{
	for (Entity* ent : entities)
	{
		ent->Start();
	}
}

void EngineModule::World::Update()
{
	for (Entity* ent : entities)
	{
		ent->Update();
	}
}
