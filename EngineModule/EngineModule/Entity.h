#pragma once
#include "BaseEntity.h"

namespace ImpEngineModule
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
		/// Entity�� �Ҵ��� ������Ʈ���� ��� �����Ѵ�.
		void DestroyAllComponents() override;

		/// TypeIndex�� �ش��ϴ� ������Ʈ�� �����Ѵ�.
		void DestroyComponent(TypeIndex index);

		/// Component���� Start�� ȣ���Ѵ�.
		void Start() override;

		/// Component���� Update�� ȣ���Ѵ�.
		void Update() override;

		/// World�� �����´� 
		World* GetWorld()const { return m_world; }

		/// Entity ������ ID�� �����´�.
		size_t GetID()const { return m_id; }

		/// Entity�� �̸��� �����´�.
		std::string& GetName() { return m_name; }

		/// Entity�� ������¸� �����´�.
		EntityState GetState()const { return m_state; }

		/// ������Ʈ�� TypeIndex�� �����´�.
		Component* GetComponent(TypeIndex index);

		/// TŸ�Կ� �ش��ϴ� ������Ʈ�� �����´�
		template <typename T>
		T* GetComponent();

		/// �������� ���ø��� ����ؼ� T Ÿ�Կ� �ش��ϴ� T(Args...)
		/// �����ڸ� ȣ���ϰ� Entity�� �߰��Ѵ�.
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args);

		/// ������Ʈ�� �����ϴ��� Ȯ���Ѵ�.
		template<typename T>
		bool HasComponent();

		/// <summary>
		/// ������Ʈ���� �����ϴ��� Ȯ���Ѵ�.
		/// </summary>
		template<typename T1, typename T2, typename... Types>
		bool HasComponent();

	private:
		World* m_world;
		size_t m_id;
		std::string m_name; 
		EntityState m_state;
		std::unordered_map<TypeIndex, Component*> m_components;

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

		return m_components.find(index) != m_components.end();
	}

	template <typename T, typename... Args>
	T* ImpEngineModule::Entity::AddComponent(Args&&... args)
	{
	 	TypeIndex index = GetTypeIndex<T>();
		
		// �̹� ������ ������Ʈ�� �������� �ʴ´�.
		if (Component* component = GetComponent(index); component !=nullptr)
		{ 
			return reinterpret_cast<T*>(component);
		}

		// �������� ���ø��� ����� ������
		Component* component = new T(args...);
		component->Set(GetWorld(), this);
		m_components.insert(make_pair(index, component));

		return component;
	}

	template <typename T>
	T* ImpEngineModule::Entity::GetComponent()
	{
		TypeIndex index = GetTypeIndex<T>();
		
		auto iter = m_components.find(index);

		if (iter == m_components.end())
			return nullptr;

		T* component = reinterpret_cast<T*>(iter->second);

		return component;
	}

}