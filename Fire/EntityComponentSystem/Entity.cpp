#include "ECSDefine.h"
#include "Entity.h"


Fire::ECS::Entity::~Entity()
{
	RemoveAll();
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