#pragma once
#include "BaseWorld.h"

namespace ImpEngineModule
{
	class Entity;
	
	/// <summary>
	/// World : Entity를 관리하는 컨테이너이다.
	/// Entity Component Base : Component가 데이터도 관리하고 로직도 수행한다.
	/// </summary>
	class World : public BaseWorld
	{
	public:
		World();
		~World();

		World(const World& other) = delete;
		World& operator =(const World& other) = delete;

	public:
		/// Entity 생성
		Entity* CreateEntity();

		/// Entity 삭제
		void DestroyEntity(Entity* ent, bool immediate = false);
		
		/// Entity 삭제
		void DestroyEntity(size_t id, bool immediate = false);

		/// Entity ID로 탐색
		Entity* GetEntity(size_t id)const;

		/// Entity 이름으로 탐색
		Entity* GetEntity(const std::string& name)const;

		/// World Reset
		void Reset() override;

		/// World 시작전에 호출
		void Start() override;

		/// 매 프레임 호출 
		void Update() override;

		/// LastEntity ID 획득
		size_t GetLastEntityID()const { return m_lastEntityID; }

	private:
		size_t m_lastEntityID = 0;
		std::vector<Entity*> m_entities;

	};
}

