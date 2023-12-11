#pragma once

namespace ImpEngineModule
{
	class Entity;
	class World;

	/// <summary>
	/// Entity Iteraotor
	/// </summary>
	class EntityIterator
	{
	public:
		EntityIterator(ImpEngineModule::World* world, size_t index
			, bool isEnd, bool isIncludeToBeDestroyed);
		
		EntityIterator& operator++();
		bool operator==(const EntityIterator& other);
		Entity* Get()const;

		/// EndIterator »Æ¿Œ
		bool IsEnd() const;

	private:
		size_t m_index;
		World* m_world;
		bool m_isEnd;
		bool m_isIncludeToBeDestroyed;
	};


}

