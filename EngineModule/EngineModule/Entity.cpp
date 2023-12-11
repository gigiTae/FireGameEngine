#include "EngineModulePCH.h"
#include "Entity.h"
#include "Component.h"

ImpEngineModule::Entity::Entity(World* world, size_t id)
	:_world(world), _id(id), _state(EntityState::Active),
	_name("Entity" + std::to_string(id))
{}

ImpEngineModule::Entity::~Entity()
{}

void ImpEngineModule::Entity::DestroyAllComponents()
{
	for (auto& iter : _components)
	{
		iter.second->UnInitialize();
		delete iter.second;
	}

	_components.clear();
}

void ImpEngineModule::Entity::DestroyComponent(TypeIndex index)
{
	auto iter = _components.find(index);

	if (iter != _components.end())
	{
		Component* component = iter->second;
		component->UnInitialize();
		delete component;
	}
}

void ImpEngineModule::Entity::Start()
{
	for (auto& iter : _components)
	{
		iter.second->Start();
	}
}

void ImpEngineModule::Entity::Update(float dt)
{
	for (auto& iter : _components)
	{
		Component* comp = iter.second;

		if (comp->IsActive())
		{
			comp->Update(dt);
		}
	}
}

ImpEngineModule::Component* ImpEngineModule::Entity::GetComponent(TypeIndex index)
{
	auto iter = _components.find(index);

	if (iter != _components.end())
	{
		return iter->second;
	}

	return nullptr;
}
