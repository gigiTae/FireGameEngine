#pragma once
#include "BaseWorld.h"

#include "ComponentHandle.h"
#include "EntityComponentView.h"

namespace ImpEngineModule
{
	class Entity;
	
	/// <summary>
	/// World : Entity�� �����ϴ� �����̳��̴�.
	/// Entity Component Base : Component�� �����͵� �����ϰ� ������ �����Ѵ�.
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
		/// Entity ����
		Entity* CreateEntity();

		/// Entity ����
		void DestroyEntity(Entity* ent, bool immediate = false);
		
		/// Entity ����
		void DestroyEntity(size_t id, bool immediate = false);

		/// Entity ID�� Ž��
		Entity* GetEntity(size_t id)const;

		/// Entity �̸����� Ž��
		Entity* GetEntity(const std::string& name)const;

		/// LastEntity ID ȹ��
		size_t GetLastEntityID()const { return _lastEntityID; }

		/// enitity size
		size_t GetSize()const { return _entities.size(); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Types">������ ������Ʈ Ÿ�Ե�</typeparam>
		/// <param name="viewFunc">�����Լ�</param>
		/// <param name="isIncludeToBeDestroyed">���������� Entity ���Կ���</param>
		template<typename... Types>
		void Each(typename std::common_type<std::function<void(Entity*, Internal::ComponentHandle<Types>...)>>::type viewFunc,
			bool isIncludeToBeDestroyed = false);


		template<typename... Types>
		Internal::EntityComponentView<Types...> Each(bool isIncludeToBeDestroyed);

#pragma endregion Entity

		/// World Reset
		void Reset() override;

		/// World �������� ȣ��
		void Start() override;

		/// �� ������ ȣ�� 
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

