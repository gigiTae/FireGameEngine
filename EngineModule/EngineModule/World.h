#pragma once
#include "BaseWorld.h"

namespace EngineModule
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
		/// <summary>
		/// Entity 생성
		/// </summary>
		Entity* CreateEntity() override;

		/// <summary>
		/// Entity 삭제
		/// </summary>
		void DestroyEntity(Entity* ent, bool immediate = false) override;
		
		/// <summary>
		/// Entity 삭제
		/// </summary>
		void DestroyEntity(size_t id, bool immediate = false) override;

		/// <summary>
		/// Entity ID로 탐색
		/// </summary>
		Entity* GetEntity(size_t id)const override;

		/// <summary>
		/// Entity 이름으로 탐색
		/// </summary>
		Entity* GetEntity(const std::string& name)const override;

		/// <summary>
		/// World Reset
		/// </summary>
		void Reset() override;

		/// <summary>
		/// World 시작전에 호출
		/// </summary>
		void Start() override;

		/// <summary>
		/// 매 프레임 호출 
		/// </summary>
		void Update() override;

	private:
		size_t lastEntityID = 0;
		std::vector<Entity*> entities;

	};
}

