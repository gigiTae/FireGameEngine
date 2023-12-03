#include "ECSDefine.h"
#include "Entity.h"


void Fire::ECS::Entity::RemoveAll()
{
	for (auto& pair : components)
	{
		pair.second->Removed(this);
		delete pair.second;
	}

	components.clear();
}