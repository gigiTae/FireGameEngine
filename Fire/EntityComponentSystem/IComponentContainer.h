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
			void* pComponent;
		public:
			IComponentContainer(void* pComponent):pComponent(pComponent){}
			virtual ~IComponentContainer() {}

			// This will be called by the entity itself
			virtual void Removed(Entity* ent) = 0;
			
			void* GetAddress()const { return pComponent; }
		};
	}
}