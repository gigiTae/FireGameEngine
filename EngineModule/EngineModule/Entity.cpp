#include "EngineModulePCH.h"
#include "Entity.h"
#include "Component.h"

ImpEngineModule::Entity::Entity(World* world, size_t id)
	:m_world(world), m_id(id), m_state(EntityState::ACTIVE),
	m_name("Entity" + std::to_string(id))
{}

ImpEngineModule::Entity::~Entity()
{}

void ImpEngineModule::Entity::DestroyAllComponents()
{
	for (auto& iter : m_components)
	{
		iter.second->UnInitialize();
		delete iter.second;
	}

	m_components.clear();
}

void ImpEngineModule::Entity::DestroyComponent(TypeIndex index)
{
	auto iter = m_components.find(index);

	if (iter != m_components.end())
	{
		Component* component = iter->second;
		component->UnInitialize();
		delete component;
	}
}

void ImpEngineModule::Entity::Start()
{
	for (auto& iter : m_components)
	{
		iter.second->Start();
	}
}

void ImpEngineModule::Entity::Update()
{
	for (auto& iter : m_components)
	{
		Component* comp = iter.second;

		if (comp->IsActive())
		{
			comp->Update();
		}
	}
}

ImpEngineModule::Component* ImpEngineModule::Entity::GetComponent(TypeIndex index)
{
	auto iter = m_components.find(index);

	if (iter != m_components.end())
	{
		return iter->second;
	}

	return nullptr;
}
