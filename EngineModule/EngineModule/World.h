#pragma once
#include "BaseWorld.h"

#include "ComponentHandle.h"
#include "EntityComponentView.h"

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

#pragma region Enitty
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

		/// LastEntity ID 획득
		size_t GetLastEntityID()const { return _lastEntityID; }

		/// enitity size
		size_t GetSize()const { return _entities.size(); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Types">쿼리할 컴포넌트 타입들</typeparam>
		/// <param name="viewFunc">람다함수</param>
		/// <param name="isIncludeToBeDestroyed">삭제예정인 Entity 포함여부</param>
		template<typename... Types>
		void Each(typename std::common_type<std::function<void(Entity*, Internal::ComponentHandle<Types>...)>>::type viewFunc,
			bool isIncludeToBeDestroyed = false);


		template<typename... Types>
		Internal::EntityComponentView<Types...> Each(bool isIncludeToBeDestroyed);

#pragma endregion Entity

		/// World Reset
		void Reset() override;

		/// World 시작전에 호출
		void Start() override;

		/// 매 프레임 호출 
		void Update(float dt) override;


	private:
		size_t _lastEntityID = 0;
		std::vector<Entity*> _entities;
	};

	template<typename... Types>
	Internal::EntityComponentView<Types...>
		ImpEngineModule::World::Each(bool isIncludeToBeDestroyed)
	{
		ImpEngineModule::Internal::EntityComponentIterator<Types...> 
			first(this, 0, false, isIncludeToBeDestroyed);

		ImpEngineModule::Internal::EntityComponentIterator<Types...>
			last(this, GetSize(), true, isIncludeToBeDestroyed);

		return Internal::EntityComponentView<Types...>(first, last);
	}

	template<typename...Types>
	void ImpEngineModule::World::Each(typename std::common_type<std::function<void(Entity*, Internal::ComponentHandle<Types>...)>>::type viewFunc,
		bool isIncludeToBeDestroyed /*= false*/)
	{
		for (Entity* ent : Each<Types...>(isIncludeToBeDestroyed))
		{
			viewFunc(ent, ent->template GetComponent<Types>()...);
		}
	}

}

