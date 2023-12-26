#include "EngineModulePCH.h"
#include "Entity.h"
#include "Component.h"
#include "World.h"

ImpEngineModule::Entity::Entity(World* world, size_t id)
	:_world(world), _id(id), _state(EntityState::Active),
	_name("Entity" + std::to_string(id))
{}

ImpEngineModule::Entity& ImpEngineModule::Entity::operator=(const Entity& other)
{
	// 월드와 ID는 복사하지 않는다.
	//_world = other._world;
	//_id = _world->AssignNewID();
	_state = other._state;
	_name = other._name;

	// 기존 컴포넌트 삭제
	DestroyAllComponents();

	for (const auto& [index, component] : other._components)
	{
		Component* clone = component->Clone();
		clone->Set(_world, this);

		_components.insert({ index,clone });
	}

	return *this;
}

ImpEngineModule::Entity::Entity(const Entity& other)
	:_world(other._world), _state(other._state), _name(other._name)
{
	_id = _world->AssignNewID();

	// 컴포넌트들의 복사
	for (const auto& [index, component] : other._components)
	{
		_components.insert({ index, component->Clone() });
	}
}

ImpEngineModule::Entity::Entity()
	:_world(nullptr), _id(0), _state(EntityState::Active)
	, _name("Entity")
{
}

ImpEngineModule::Entity::~Entity()
{
	DestroyAllComponents();
}

void ImpEngineModule::Entity::DestroyAllComponents()
{
	for (auto& iter : _components)
	{
		iter.second->Finalize();
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
		component->Finalize();
		delete component;
		_components.erase(iter);
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

ImpEngineModule::Component* ImpEngineModule::Entity::AddComponent(void* component, TypeIndex index)
{
	Component* comp = reinterpret_cast<Component*>(component);

	assert(_components.find(index) == _components.end() && "중복된 컴포넌트입니다.");


	comp->Set(_world, this);

	_components.insert({ index,comp });

	return comp;
}

bool ImpEngineModule::Entity::HasComponent(TypeIndex index)
{
	return _components.find(index) != _components.end();
}
