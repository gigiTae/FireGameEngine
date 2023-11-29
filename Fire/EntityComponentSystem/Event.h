#pragma once

namespace Fire
{
	namespace ECS
	{
		class Entity;
		template <typename T>
		class ComponentHandle;

		namespace Events
		{
			// Called when a new entity is created
			struct OnEntityCreated
			{
				Entity* entity;
			};

			// Called when an entity is about to be destroyed
			struct OnEntityDestroyed
			{
				Entity* entity;
			};

			template<typename T>
			struct OnComponentCreated
			{
				Entity* entity;
				ComponentHandle<T> component;
			};

			//Called when a component is removed
			template<typename T>
			struct OnComponentRemoved
			{
				Entity* entity;
				ComponentHandle<T> component;
			};


		}


	}

}
