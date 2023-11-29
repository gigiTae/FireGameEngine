#pragma once

#include "ECSHeader.h"
#include "ComponentContainer.h"
#include "ComponentHandle.h"

namespace Fire
{
	namespace ECS
	{
		class World;

		class Entity
		{
			friend class World;	
		public:
			Entity(World* world, size_t id) : world(world), id(id) {};

			World* GetWorld() const { return world; }

			template<typename T>
			bool Has() const
			{
				auto index = GetTypeIndex<T>();
				return components.find(index) != components.end();
			}

			template<typename T1, typename T2, typename... Types>
			bool Has() const
			{
				return Has<T1>() && Has<T2, Types...>();
			}

			template <typename ComponentType, typename... Args>
			ComponentHandle<ComponentType> Assign(Args&&... args);

			template <typename ComponentType>
			ComponentHandle<ComponentType> Get();

			template<typename ComponentType>
			bool RemoveComponent();

			/// <summary>
			/// Remove all compoenets from this entity.
			/// </summary>
			void RemoveAll();

			/// <summary>
			/// Call a function with compoents from this entity as arguments. This will return true if this entity has
			/// all specified components attached, and false if otherwise
			/// </summary>
			template<typename... Types>
			bool With(typename std::common_type<std::function<void(ComponentHandle<Types>...)>>::type view);

			size_t GetId() const { return id; }

			bool IsPedingDestroy()const { return isPedingDestroy; }
			
			const std::unordered_map<TypeIndex, IComponentContainer*>& GetComponents() const { return components; }

		private:
			std::unordered_map<TypeIndex, IComponentContainer*> components;
			World* world;

			size_t id = 0;
			bool isPedingDestroy = false;
		};


		template<typename ComponentType, typename ...Args>
		inline ComponentHandle<ComponentType> Entity::Assign(Args&&... args)
		{
			TypeIndex type = GetTypeIndex<ComponentType>();
			auto iter = components.find(type);

			if (iter != components.end()) // 새로운것으로 대체
			{
				ComponentContainer<ComponentType>* container = reinterpret_cast<ComponentContainer<ComponentType>*>(iter->second);
				container->component = ComponentType(args...);

				return ComponentHandle<ComponentType>(&container->component);
			}
			else  // new 
			{
				// allocator 를 사용해서 최적화 방법
				/*Internal::ComponentContainer<T>* container = std::allocator_traits<ComponentAllocator>::allocate(alloc, 1);
				std::allocator_traits<ComponentAllocator>::construct(alloc, container, T(args...));*/

				ComponentContainer<ComponentType>* container = new ComponentContainer<ComponentType>();
				container->component = ComponentType(args...);

				components.insert(std::make_pair(type, container));

				return ComponentHandle<ComponentType>(&container->component);
			}
		}

		template<typename ComponentType>
		inline ComponentHandle<ComponentType> Entity::Get()
		{
			TypeIndex type = GetTypeIndex<ComponentType>();

			auto iter = components.find(type);

			if (iter == components.end())
				return ComponentHandle<ComponentType>();

			ComponentContainer<ComponentType>* container =
				reinterpret_cast<ComponentContainer<ComponentType>*>(iter->second);

			return ComponentHandle<ComponentType>(&container->component);
		}

		template<typename ComponentType>
		inline bool Entity::RemoveComponent()
		{
			auto iter = components.find(GetTypeIndex<ComponentType>());

			if (iter != components.end())
			{
				iter->second->Removed(this);
				delete iter->second; // 소멸

				components.erase(iter);
				return true;
			}


			return false;
		}

		template<typename ...Types>
		inline bool Entity::With(typename std::common_type<std::function<void(ComponentHandle<Types>...)>>::type view)
		{
			if (!Has<Types...>())
				return false;

			view(Get<Types>()...); // variadic template if fun?
			return true;
		}


	}

}

