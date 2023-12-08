#include "EngineModulePCH.h"
#include "Entity.h"
#include "Component.h"

EngineModule::Entity::Entity(World* world, size_t id)
	:world(world), id(id), state(EntityState::ACTIVE),
	name("Entity" + std::to_string(id))
{}

EngineModule::Entity::~Entity()
{}

void EngineModule::Entity::DestroyAllComponents()
{
	for (auto& iter : components)
	{
		iter.second->UnInitialize();
		delete iter.second;
	}

	components.clear();
}

void EngineModule::Entity::DestroyComponent(TypeIndex index)
{
	auto iter = components.find(index);

	if (iter != components.end())
	{
		Component* component = iter->second;
		component->UnInitialize();
		delete component;

		// TODO :: Remove Call Back? 
	}


}

void EngineModule::Entity::Start()
{
	for (auto& iter : components)
	{
		iter.second->Start();
	}
}

void EngineModule::Entity::Update()
{
	for (auto& iter : components)
	{
		Component* comp = iter.second;

		if (comp->IsActive())
		{
			comp->Update();
		}
	}
}

EngineModule::Component* EngineModule::Entity::GetComponent(TypeIndex index)
{
	auto iter = components.find(index);

	if (iter != components.end())
	{
		return iter->second;
	}

	return nullptr;
}
