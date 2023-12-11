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
	public:
		enum class EntityState : int
		{
			Active, // Ȱ��ȭ
			ToBeDestroyed, // ���� ����
			Destroyed, // ����
		};

	public:
		Entity(World* world, size_t id);
		~Entity() override;

	public:

		/// Entity�� �Ҵ��� ������Ʈ���� ��� �����Ѵ�.
		void DestroyAllComponents() override;

		/// TypeIndex�� �ش��ϴ� ������Ʈ�� �����Ѵ�.
		void DestroyComponent(TypeIndex index);

		/// Component���� Start�� ȣ���Ѵ�.
		void Start() override;

		/// Component���� Update�� ȣ���Ѵ�.
		void Update(float dt) override;

		/// World�� �����´� 
		World* GetWorld()const { return _world; }

		/// Entity ������ ID�� �����´�.
		size_t GetID()const { return _id; }

		/// Entity�� �̸��� �����´�.
		std::string& GetName() { return _name; }

		/// Entity�� ������¸� �����´�.
		EntityState GetState()const { return _state; }

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
		
		// �̹� ������ ������Ʈ�� �������� �ʴ´�.
		if (Component* component = GetComponent(index); component !=nullptr)
		{
			return reinterpret_cast<T*>(component);
		}

		// �������� ���ø��� ����� ������
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