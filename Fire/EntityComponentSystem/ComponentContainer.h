#pragma once

#include "IComponentContainer.h"
#include "ComponentHandle.h"

namespace Fire
{
	namespace ECS
	{
		/// <summary>
		/// Component
		/// </summary>
		template <typename ComponentType>
		struct ComponentContainer : public IComponentContainer
		{
			ComponentContainer():IComponentContainer(&component), component()
			{};
			ComponentContainer(const ComponentType& component) :IComponentContainer(&component), component(component)
			{}

			ComponentType component;

		protected:
			void Removed(class Fire::ECS::Entity* ent) override;

		};

	}
}

