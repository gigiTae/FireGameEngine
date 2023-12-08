#pragma once
#include "BaseEntity.h"

namespace EngineModule
{
	class World;
	class Component;


	/// <summary>
	/// 컴포넌트들을 관리하는 컨테이너 역할을 한다.
	/// Entity는 컴포넌트를 관리하는 로직외에는 아무런 로직을 수행하지않는다. 
	/// </summary>
	class Entity : public BaseEntity
	{
		enum class EntityState : int
		{
			ACTIVE, // 활성화
			TO_BE_DESTROYED, // 삭제 예정
			DESTROYED, // 삭제
		};

	public:
		Entity(World* world, size_t id);
		~Entity();

	public:
		/// <summary>
		/// Entity에 할당한 컴포넌트들을 모두 삭제한다.
		/// </summary>
		void DestroyAllComponents() override;

		/// <summary>
		/// TypeIndex에 해당하는 컴포넌트를 삭제한다.
		/// </summary>
		void DestroyComponent(TypeIndex index);

		/// <summary>
		/// Component들의 Start를 호출한다.
		/// </summary>
		void Start() override;

		/// <summary>
		/// Component들의 Update를 호출한다.
		/// </summary>
		void Update() override;

		/// <summary>
		/// World를 가져온다 
		/// </summary>
		World* GetWorld()const { return world; }

		/// <summary>
		/// Entity 고유의 ID를 가져온다.
		/// </summary>
		size_t GetID()const { return id; }

		/// <summary>
		/// Entity의 이름을 가져온다.
		/// </summary>
		std::string& GetName() { return name; }

		/// <summary>
		/// Entity의 현재상태를 가져온다.
		/// </summary>
		EntityState GetState()const { return state; }

		/// <summary>
		/// 컴포넌트를 TypeIndex로 가져온다.
		/// </summary>
		Component* GetComponent(TypeIndex index);

		/// <summary>
		/// T타입에 해당하는 컴포넌트를 가져온다
		/// </summary>
		template <typename T>
		T* GetComponent();

		/// <summary>
		/// 가변인자 템플릿을 사용해서 T 타입에 해당하는 T(Args...)
		/// 생성자를 호출하고 Entity에 추가한다.
		/// </summary>
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args);

		/// <summary>
		/// 컴포넌트를 소유하는지 확인한다.
		/// </summary>
		template<typename T>
		bool HasComponent();

		template<typename T1, typename T2, typename... Types>
		bool HasComponent();

	private:
		World* world;
		size_t id;
		std::string name; 
		EntityState state;
		std::unordered_map<TypeIndex, Component*> components;

		friend class World;
	};

	template<typename T1, typename T2, typename... Types>
	bool EngineModule::Entity::HasComponent()
	{
		return HasComponent<T1>() && HasComponent<T2, Types...>();
	}

	template<typename T>
	bool EngineModule::Entity::HasComponent()
	{
		TypeIndex index = GetTypeIndex();

		return components.find() != components.end();
	}

	template <typename T, typename... Args>
	T* EngineModule::Entity::AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::type, "Component를 상속받아야합니다");

	 	TypeIndex index = GetTypeIndex<T>();
		
		// 이미 생성한 컴포넌트는 생성하지 않는다.
		if (Component* component = GetComponent(index); component !=nullptr)
		{
			return component;
		}

		// 가변인자 템플릿을 사용한 생성자
		Component* component = new T(args...);

		components.insert(make_pair(index, component));

		return component;
	}

	template <typename T>
	T* EngineModule::Entity::GetComponent()
	{
		TypeIndex index = GetTypeIndex<T>();
		
		auto iter = components.find(index);

		if (iter == components.end())
			return nullptr;

		T* component = reinterpret_cast<T*>(iter->second);

		return component;
	}

}