#pragma once
#include "BaseEntity.h"

namespace EngineModule
{
	class World;
	class Component;


	/// <summary>
	/// ������Ʈ���� �����ϴ� �����̳� ������ �Ѵ�.
	/// Entity�� ������Ʈ�� �����ϴ� �����ܿ��� �ƹ��� ������ ���������ʴ´�. 
	/// </summary>
	class Entity : public BaseEntity
	{
		enum class EntityState : int
		{
			ACTIVE, // Ȱ��ȭ
			TO_BE_DESTROYED, // ���� ����
			DESTROYED, // ����
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
		static_assert(std::is_base_of<Component, T>::type, "Component�� ��ӹ޾ƾ��մϴ�");

	 	TypeIndex index = GetTypeIndex<T>();
		
		// �̹� ������ ������Ʈ�� �������� �ʴ´�.
		if (Component* component = GetComponent(index); component !=nullptr)
		{
			return component;
		}

		// �������� ���ø��� ����� ������
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