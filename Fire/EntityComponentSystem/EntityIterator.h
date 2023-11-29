#pragma once

namespace Fire
{
	namespace ECS
	{
		class World;
		class Entity;

		namespace Internal
		{
			class EntityIterator
			{
			public:
				EntityIterator(World* world, size_t index
					, bool isEnd, bool isIncludePendingDestroy);

				size_t GetIndex() const { return index; }

				bool IsEnd() const;

				bool IsIncludePedingDestroy() const { return isIncludePedingDestroy; }

				World* GetWorld()const { return world; }

				Entity* Get() const;

				Entity* operator*() const { return Get(); }

				bool operator==(const EntityIterator& other) const
				{
					if (world != other.world)
						return false;

					if (IsEnd())
						return other.IsEnd();

					return index == other.index;
				}

				bool operator !=(const EntityIterator& other) const
				{
					if (world != other.world)
						return true;

					if (IsEnd())
						return !other.IsEnd();

					return index != other.index;
				}
			
				EntityIterator& operator++();

			private:
				size_t index;
				bool isEnd = false;

				class ECS::World* world;
				bool isIncludePedingDestroy;
 			};
		}

	}
}


