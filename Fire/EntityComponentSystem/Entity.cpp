#include "ECSDefine.h"
#include "Entity.h"
#include "ReflectionHeader.h"

Fire::ECS::Entity::~Entity()
{
	RemoveAll();
}

bool Fire::ECS::Entity::RemoveComponent(TypeIndex index)
{
	auto iter= components.find(index);
	if (iter == components.end())
		return false;

	delete iter->second;
	iter = components.erase(iter);

	return true;
}

void Fire::ECS::Entity::Assign(TypeIndex index)
{
	using namespace Fire::Reflect;

	if (components.find(index) != components.end())
		return;

	// 리플렉션
	TypeDescriptor* desc = TypeMap::GetTypeMap()->GetTypeDescriptor(index);
	IComponentContainer* container =  desc->GetComponent();

	components.insert({ index, container });
}

void Fire::ECS::Entity::RemoveAll()
{
	for (auto& pair : components)
	{
		pair.second->Removed(this);
		delete pair.second;
	}

	components.clear();
}