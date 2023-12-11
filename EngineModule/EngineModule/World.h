#pragma once
#include "BaseWorld.h"

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

		/// World Reset
		void Reset() override;

		/// World �������� ȣ��
		void Start() override;

		/// �� ������ ȣ�� 
		void Update() override;

		/// LastEntity ID ȹ��
		size_t GetLastEntityID()const { return m_lastEntityID; }

	private:
		size_t m_lastEntityID = 0;
		std::vector<Entity*> m_entities;

	};
}

