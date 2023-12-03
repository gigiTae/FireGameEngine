#pragma once

#include "ECSDefine.h"


namespace Fire
{
	namespace ECS
	{
		class World;
		class Entity;

		class IComponentContainer
		{
		public:
			virtual ~IComponentContainer() {}

			// This will be called by the entity itself
			virtual void Removed(Entity* ent) = 0;
		};
	}
}