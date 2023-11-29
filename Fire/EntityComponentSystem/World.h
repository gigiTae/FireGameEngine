#pragma once

#include "ECSHeader.h"
#include "EventSubscriber.h"
#include "EntityComponentIterator.h"
#include "EntityComponentView.h"

namespace Fire
{
	namespace ECS
	{
		namespace Internal
		{
			class EntityView;

			class EntityIterator;
		}
		class Entity;
		class IEntitySystem;
		class ISubscriber;

		template<typename T>
		class EventSubscriber;

		template<typename T>
		class ComponentHandle;

		class World
		{
		public:
			World();
			~World();

			
			/// <summary>
			/// Destroy an entity. this will emit the OnEntityDestroy event.
			/// </summary>
			void Destroy(Entity* ent, bool immediate = false);

			/// <summary>
			/// Delete all entities in the peding destroy queue. Returns true is any entities 
			/// were  cleaned up false if there were no entities to clean up.
			/// </summary>
			bool Cleanup();

			/// <summary>
			/// Reset the world, destroying all entites. 
			/// Entity ids will be reset as well
			/// </summary>
			void Reset();

			/// <summary>
			/// Register a system, The world will manage 
			/// the memory of the system unless you unregiter the system. 
			/// </summary>
			IEntitySystem* RegisterSystem(IEntitySystem* system);

			/// <summary>
			/// Unregister a system.
			/// </summary>
			void UnregisterSystem(IEntitySystem* system);

			/// <summary>
			/// Active a system.
			/// </summary>
			void EnableSystem(IEntitySystem* system);

			/// <summary>
			/// Disable a system.
			/// </summary>
			void DisableSystem(IEntitySystem* system);

			/// <summary>
			/// Subscribe to an event.
			/// </summary>
			template <typename T>
			void Subscribe(EventSubscriber<T>* subscriber);

			/// <summary>
			/// Unsubscrine to an event. 
			/// </summary>
			template <typename T>
			void Unsubscribe(EventSubscriber<T>* subscriber);

			/// <summary>
			/// Unsubscribe from all events. 
			/// Don't be afraid of the void pointer,
			/// just pass in your subscriber as normal
			/// </summary>
			void UnsubscribeAll(void* subscriber);

			/// <summary>
			/// Emti an event. This will do nothing if there aro no 
			/// subscribers for the event type.
			/// </summary>
			template<typename T>
			void Emit(const T& event);

			/// <summary>
			/// Run a function on each entity with a specific set of components.
			/// This is useful for implementing an EntitySystem.
			/// If you want to include entities that are peding destruction,
			/// set includePendingDestory to true.
			/// </summary>
			template<typename... Types>
			void Each(typename std::common_type<std::function<void(Entity*, ComponentHandle<Types>...)>>::type viewFunc
				, bool isIncludePedingDestroy = false);

			/// <summary>
			/// Get a view for entities with a specific set of component.
			/// The list of entities is calculated on the fly, so this method itself
			/// has little overhead, This is mostly useful with a range for loop;
			/// </summary>
			template<typename... Types>
			Internal::EntityComponentView<Types...> Each(bool isIncludePedingDestroy = false);

			/// <summary>
			/// Run a function on all entities.
			/// </summary>
			void All(std::function<void(Entity*)> viewFunc, bool isIncludePedingDestroy = false);

			Internal::EntityView All(bool isIncludePedingDestroy = false);	

			size_t GetCount() const { return entities.size(); }

			Entity* Create();
			
			Entity* GetByIndex(size_t index);
			
			Entity* GetById(size_t id);

			void Tick(float dt);

		private:
			size_t lastEntityId = 0;
			std::vector<Entity*> entities;
			std::vector<IEntitySystem*> systems;
			std::vector<IEntitySystem*> disabledSystems;
			std::unordered_map<TypeIndex,
				std::vector<ISubscriber*>> subscirbers;

		};

		template<typename T>
		inline void World::Subscribe(EventSubscriber<T>* subscriber)
		{
			auto index = GetTypeIndex<T>();
			auto iter = subscirbers.find(index);

			if (iter == subscirbers.end())
			{
				std::vector<ISubscriber*> vec;
				vec.push_back(subscriber);
				subscirbers.insert(std::make_pair(index, vec));
			}
			else
			{
				iter->second.push_back(subscriber);
			}
		}

		template<typename T>
		inline void World::Unsubscribe(EventSubscriber<T>* subscriber)
		{
			TypeIndex index = GetTypeIndex<T>();
			auto iter = subscirbers.find(index);
			if (iter != subscirbers.end()) // vector ¼øÈ¸
			{
				auto& vec = iter->second;
				vec.erase(std::find(vec.begin(), vec.end(), subscriber), vec.end());

				if (vec.size() == 0) //  clear
				{
					subscirbers.erase(iter);
				}
			}
		}

		template<typename T>
		inline void World::Emit(const T& event)
		{
			auto iter = subscirbers.find(GetTypeIndex<T>());
			
			if (iter != subscirbers.end())
			{
				for (auto* base : iter->second)
				{
					auto* sub = reinterpret_cast<EventSubscriber<T>*>(base);
					sub->Receive(this, event);
				}
			}
		}

		template<typename ...Types>
		inline void World::Each(typename std::common_type<std::function<void(Entity*, ComponentHandle<Types>...)>>::type viewFunc, bool isIncludePedingDestroy)
		{
			for (auto* ent : Each<Types...>(isIncludePedingDestroy))
			{
				viewFunc(ent, ent->template Get<Types>()...);
			}
		}

		template<typename ...Types>
		inline Fire::ECS::Internal::EntityComponentView<Types...> World::Each(bool isIncludePedingDestroy)
		{
			Fire::ECS::Internal::EntityComponentIterator<Types...> first (this, 0, false, isIncludePedingDestroy);
			Fire::ECS::Internal::EntityComponentIterator<Types...> last (this, GetCount(), true, isIncludePedingDestroy);
			return Fire::ECS::Internal::EntityComponentView<Types...>(first, last);
		}

		template<typename ComponentType>
		inline void ComponentContainer<ComponentType>::Removed(Fire::ECS::Entity* ent)
		{
			auto handle = ComponentHandle<ComponentType>(&component);
			Events::OnComponentRemoved<ComponentType> removeEvent{ ent,handle };
			ent->GetWorld()->Emit<Events::OnComponentRemoved<ComponentType>>(removeEvent);
		}
	}

}