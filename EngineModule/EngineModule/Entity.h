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
		/// <summary>
		/// Entity�� �Ҵ��� ������Ʈ���� ��� �����Ѵ�.
		/// </summary>
		void DestroyAllComponents() override;

		/// <summary>
		/// TypeIndex�� �ش��ϴ� ������Ʈ�� �����Ѵ�.
		/// </summary>
		void DestroyComponent(TypeIndex index);

		/// <summary>
		/// Component���� Start�� ȣ���Ѵ�.
		/// </summary>
		void Start() override;

		/// <summary>
		/// Component���� Update�� ȣ���Ѵ�.
		/// </summary>
		void Update() override;

		/// <summary>
		/// World�� �����´� 
		/// </summary>
		World* GetWorld()const { return world; }

		/// <summary>
		/// Entity ������ ID�� �����´�.
		/// </summary>
		size_t GetID()const { return id; }

		/// <summary>
		/// Entity�� �̸��� �����´�.
		/// </summary>
		std::string& GetName() { return name; }

		/// <summary>
		/// Entity�� ������¸� �����´�.
		/// </summary>
		EntityState GetState()const { return state; }

		/// <summary>
		/// ������Ʈ�� TypeIndex�� �����´�.
		/// </summary>
		Component* GetComponent(TypeIndex index);

		/// <summary>
		/// TŸ�Կ� �ش��ϴ� ������Ʈ�� �����´�
		/// </summary>
		template <typename T>
		T* GetComponent();

		/// <summary>
		/// �������� ���ø��� ����ؼ� T Ÿ�Կ� �ش��ϴ� T(Args...)
		/// �����ڸ� ȣ���ϰ� Entity�� �߰��Ѵ�.
		/// </summary>
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args);

		/// <summary>
		/// ������Ʈ�� �����ϴ��� Ȯ���Ѵ�.
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