#include "EngineModulePCH.h"
#include "World.h"
#include "Entity.h"
#include "Transform.h"
#include "Event.h"
#include "EventManager.h"

ImpEngineModule::World::World()
	:_lastEntityID(0) ,_entities{},_eventManager(nullptr),
	_inputManager(nullptr),_resourceManager(nullptr)
{
}

ImpEngineModule::World::~World()
{

}

void ImpEngineModule::World::Initialize(EventManager* eventMgr, InputManager* inputMgr, ResourceManager* resMgr)
{
	_eventManager = eventMgr;
	_inputManager = inputMgr;
	_resourceManager = resMgr;
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

void ImpEngineModule::World::Finalize()
{
	Reset();
}

ImpEngineModule::Entity* ImpEngineModule::World::CreateEntity()
{
	/// TODO : 나중에는 오브젝트 풀을 사용해서 관리한다.
	++_lastEntityID;
	Entity* ent = new Entity(this, _lastEntityID);

	_entities.push_back(ent);
	_eventManager->Emit<Event::OnEntityCreated>({ ent });

	return ent;
}

void ImpEngineModule::World::DestroyEntity(Entity* ent)
{
	if (ent == nullptr || ent->GetState() != Entity::EntityState::Active)
	{
		return; 
	}

	ent->_state = Entity::EntityState::ToBeDestroyed;   
	_eventManager->Emit<Event::OnEntityDestroyed>({ ent });

	// 자식들도 모두 삭제한다.
	auto& children = ent->GetComponent<Transform>()->GetChildren();

	for (Transform* childT : children)
	{
		Entity* child =  childT->GetEntity();
		DestroyEntity(child);
	}
}

ImpEngineModule::Entity* ImpEngineModule::World::GetByIndex(size_t index) const
{
	if (_entities.size() <= index)
		return nullptr;

	return _entities[index];
}

void ImpEngineModule::World::DestroyEntity(size_t id)
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

ImpEngineModule::Internal::EntityView ImpEngineModule::World::All(bool isIncludeToBeDestroyed /*= false*/)
{
	Internal::EntityIterator first(this, 0, false, isIncludeToBeDestroyed);
	Internal::EntityIterator last(this, GetSize(), true, isIncludeToBeDestroyed);

	return Internal::EntityView(first, last);
}

void ImpEngineModule::World::All(std::function<void(Entity*)> viewFunc, bool isIncludeToBeDestroyed /*= false*/)
{
	for (Entity* ent : All(isIncludeToBeDestroyed))
	{
		viewFunc(ent);
	}
}
