#pragma once
#include "BaseEntity.h"

namespace ImpEngineModule
{
	class World;
	class Component;

	/// <summary>
	/// 컴포넌트들을 관리하는 컨테이너 역할을 한다.
	/// Entity는 컴포넌트를 관리하는 로직외에는 아무런 로직을 수행하지않는다. 
	/// </summary>
	class Entity : public BaseEntity
	{
	public:
		enum class EntityState : int
		{
			Active, // 활성화
			ToBeDestroyed, // 삭제 예정
			Destroyed, // 삭제
		};

	public:
		Entity(World* world, size_t id);
		~Entity() override;

	public:

		/// Entity에 할당한 컴포넌트들을 모두 삭제한다.
		void DestroyAllComponents() override;

		/// TypeIndex에 해당하는 컴포넌트를 삭제한다.
		void DestroyComponent(TypeIndex index);

		/// Component들의 Start를 호출한다.
		void Start() override;

		/// Component들의 Update를 호출한다.
		void Update(float dt) override;

		/// World를 가져온다 
		World* GetWorld()const { return _world; }

		/// Entity 고유의 ID를 가져온다.
		size_t GetID()const { return _id; }

		/// Entity의 이름을 가져온다.
		std::string& GetName() { return _name; }

		/// Entity의 현재상태를 가져온다.
		EntityState GetState()const { return _state; }

		/// 컴포넌트를 TypeIndex로 가져온다.
		Component* GetComponent(TypeIndex index);

		/// T타입에 해당하는 컴포넌트를 가져온다
		template <typename T>
		T* GetComponent();

		/// 가변인자 템플릿을 사용해서 T 타입에 해당하는 T(Args...)
		/// 생성자를 호출하고 Entity에 추가한다.
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args);

		/// 컴포넌트를 소유하는지 확인한다.
		template<typename T>
		bool HasComponent();

		/// <summary>
		/// 컴포넌트들을 소유하는지 확인한다.
		/// </summary>
		template<typename T1, typename T2, typename... Types>
		bool HasComponent();

	private:
		World* _world;
		size_t _id;
		std::string _name; 
		EntityState _state;
		std::unordered_map<TypeIndex, Component*> _components;

		friend class World;
	};

	template<typename T1, typename T2, typename... Types>
	bool ImpEngineModule::Entity::HasComponent()
	{
		return HasComponent<T1>() && HasComponent<T2, Types...>();
	}

	template<typename T>
	bool ImpEngineModule::Entity::HasComponent()
	{
		TypeIndex index = GetTypeIndex<T>();

		return _components.find(index) != _components.end();
	}

	template <typename T, typename... Args>
	T* ImpEngineModule::Entity::AddComponent(Args&&... args)
	{
	 	TypeIndex index = GetTypeIndex<T>();
		
		// 이미 생성한 컴포넌트는 생성하지 않는다.
		if (Component* component = GetComponent(index); component !=nullptr)
		{
			return reinterpret_cast<T*>(component);
		}

		// 가변인자 템플릿을 사용한 생성자
		T* component = new T(args...);
		component->Set(GetWorld(), this);

		_components.insert(make_pair(index, component));

		return component;
	}

	template <typename T>
	T* ImpEngineModule::Entity::GetComponent()
	{
		TypeIndex index = GetTypeIndex<T>();
		
		auto iter = _components.find(index);

		if (iter == _components.end())
			return nullptr;

		T* component = reinterpret_cast<T*>(iter->second);

		return component;
	}

}