#include "World.h"
#include "Entity.h"
#include "IEntitySystem.h"
#include "EntityView.h"

Fire::ECS::World::World()
	:entities{}
	,systems{}
	,lastEntityId(0)
{
}

Fire::ECS::World::~World()
{
	Reset();
}

Fire::ECS::Entity* Fire::ECS::World::Create()
{
	++lastEntityId;

	Entity* ent = new Entity(this, lastEntityId);

	entities.push_back(ent);

	Emit<Events::OnEntityCreated>({ ent });	
	
	return ent;
}

Fire::ECS::Entity* Fire::ECS::World::GetByIndex(size_t index)
{
	if (entities.size() <= index)
		return nullptr;

	return entities[index];
}

Fire::ECS::Entity* Fire::ECS::World::GetById(size_t id)
{
	if (lastEntityId <= id)
		return nullptr;

	for (auto ent : entities)
	{
		if (ent->GetId() == id)
		{
			return ent;
		}
	}

	return nullptr;
}

void Fire::ECS::World::Tick(float dt)
{
	for (auto* system : systems)
	{
		system->Tick(this,dt);
	}

}

bool Fire::ECS::World::Cleanup()
{
	size_t count = 0;
	entities.erase(std::remove_if(entities.begin(), entities.end(),
		[&, this](Entity* ent){
			if (ent->IsPedingDestroy())
			{
				delete ent;
				++count;
				return true;
			}

			return false;
		}), entities.end());

	return count > 0;
}

void Fire::ECS::World::Destroy(Entity* ent, bool immediate)
{
	if (ent == nullptr)
		return;

	if (ent->IsPedingDestroy())
	{
		if (immediate)
		{
			entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
			delete ent;
		}

		return;
	}

	ent->isPedingDestroy = true;

	Emit<Events::OnEntityDestroyed>({ ent });

	if (immediate)
	{
		entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
		delete ent;
	}
}

Fire::ECS::IEntitySystem* Fire::ECS::World::RegisterSystem(IEntitySystem* system)
{
	systems.push_back(system);
	system->Configure(this);

	return system;
}

void Fire::ECS::World::UnregisterSystem(IEntitySystem* system)
{
	// c++ : std::remove( begine, end, 비교) -> 삭제할 시작점 iterator 반환 
	systems.erase(std::remove(systems.begin(), systems.end(), system), systems.end());
	system->Unconfigure(this);
}

void Fire::ECS::World::Reset()
{
	for (auto* ent : entities)
	{
		if (!ent->IsPedingDestroy())
		{
			ent->isPedingDestroy = true;
			Emit<Events::OnEntityDestroyed>({ ent });
		}
		delete ent;
	}
	
	entities.clear();
	lastEntityId = 0;
}

void Fire::ECS::World::EnableSystem(IEntitySystem* system)
{
	auto iter = std::find(disabledSystems.begin(), disabledSystems.end(), system);

	if (iter != disabledSystems.end())
	{
		disabledSystems.erase(iter);
		systems.push_back(system);
	}
}

void Fire::ECS::World::DisableSystem(IEntitySystem* system)
{
	auto iter = std::find(systems.begin(), systems.end(), system);

	if (iter != systems.end())
	{
		systems.erase(iter);
		disabledSystems.push_back(system);
	}
}

void Fire::ECS::World::UnsubscribeAll(void* subscriber)
{
	for (auto& kv : subscirbers)
	{
		kv.second.erase(std::remove(kv.second.begin(), kv.second.end(), subscriber), kv.second.end());
		if (kv.second.size() == 0)
		{
			subscirbers.erase(kv.first);
		}

	}
}

void Fire::ECS::World::All(std::function<void(Entity*)> viewFunc, bool isIncludePedingDestroy)
{
	for (Entity* ent : All(isIncludePedingDestroy))
	{
		viewFunc(ent);
	}

}

Fire::ECS::Internal::EntityView Fire::ECS::World::All(bool isIncludePedingDestroy)
{
	Internal::EntityIterator first(this, 0, false, isIncludePedingDestroy);
	Internal::EntityIterator last(this, GetCount(), true, isIncludePedingDestroy);

	return Fire::ECS::Internal::EntityView(first, last);
}

