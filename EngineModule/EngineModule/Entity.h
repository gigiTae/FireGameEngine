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
		void RemoveAll() override;

		void Remove(TypeIndex index);

		void Start() override;

		void Update() override;

		World* GetWorld()const { return world; }
		
		size_t GetID()const { return id; }
		
		std::string& GetName() { return name; }

		EntityState GetState()const { return state; }

		Component* GetComponent(TypeIndex index);
		
		template <typename T>
		T* GetComponent();

		template <typename T, typename... Args>
		T* AddComponent(Args&&... args);

	private:
		World* world;
		size_t id;
		std::string name; 
		EntityState state;
		std::unordered_map<TypeIndex, Component*> components;

		friend class World;
	};

	template <typename T, typename... Args>
	T* EngineModule::Entity::AddComponent(Args&&... args)
	{
		Component* component = new T(args...);
		

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