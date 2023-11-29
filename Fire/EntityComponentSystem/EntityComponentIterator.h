#pragma once

#include"Entity.h"

namespace Fire
{
	namespace ECS
	{
		class World;
		class Entity;

		namespace Internal
		{
			template<typename... Types>
			class EntityComponentIterator
			{
			public:
				EntityComponentIterator(World* world, size_t index
					, bool isEnd, bool isIncludePendingDestroy);

				size_t GetIndex() const { return index; }

				bool IsEnd() const;

				bool IsIncludePedingDestroy() const { return isIncludePedingDestroy; }

				World* GetWorld() const { return world; }

				Entity* Get()const;
				
				Entity* operator*()const { return Get(); }

				bool operator==(const EntityComponentIterator<Types...>& other) const
				{
					if (world != other.world)
						return false;

					if (IsEnd())
						return other.IsEnd();

					return index == other.index;
				}

				bool operator!=(const EntityComponentIterator<Types...>& other) const
				{
					if (world != other.world)
						return true;

					if (IsEnd())
						return !other.IsEnd();

					return index != other.index;
				}
				
				EntityComponentIterator<Types...>& operator++();

			private:
				bool isEnd = false;
				size_t index;
				class ECS::World* world;
				bool isIncludePedingDestroy;
			};

			template<typename ...Types>
			inline EntityComponentIterator<Types...>::EntityComponentIterator(World* world,
				size_t index, bool isEnd, bool isIncludePedingDestroy)
				:isEnd(isEnd), index(index), world(world),
				isIncludePedingDestroy(isIncludePedingDestroy)
			{
			}

			template<typename ...Types>
			inline bool EntityComponentIterator<Types...>::IsEnd() const
			{
				return isEnd || index >= world->GetCount();
			}

			template<typename ...Types>
			inline Entity* EntityComponentIterator<Types...>::Get() const
			{
				if (IsEnd())
					return nullptr;

				return world->GetByIndex(index);
			}

			template<typename ...Types>
			inline EntityComponentIterator<Types...>& EntityComponentIterator<Types...>::operator++()
			{
				++index;
				while (index < world->GetCount()
					&& (Get() == nullptr || !Get()->template Has<Types...>() || (Get()->IsPedingDestroy() && !IsIncludePedingDestroy())))
				{
					++index;
				}

				if (index >= world->GetCount())
					isEnd = true;

				return *this;
			}

		}
	}
}