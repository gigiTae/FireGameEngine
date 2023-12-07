#pragma once
#include "BaseWorld.h"

namespace EngineModule
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
		/// <summary>
		/// Entity ����
		/// </summary>
		Entity* CreateEntity() override;

		/// <summary>
		/// Entity ����
		/// </summary>
		void DestroyEntity(Entity* ent, bool immediate = false) override;
		
		/// <summary>
		/// Entity ����
		/// </summary>
		void DestroyEntity(size_t id, bool immediate = false) override;

		/// <summary>
		/// Entity ID�� Ž��
		/// </summary>
		Entity* GetEntity(size_t id)const override;

		/// <summary>
		/// Entity �̸����� Ž��
		/// </summary>
		Entity* GetEntity(const std::string& name)const override;

		/// <summary>
		/// World Reset
		/// </summary>
		void Reset() override;

		/// <summary>
		/// World �������� ȣ��
		/// </summary>
		void Start() override;

		/// <summary>
		/// �� ������ ȣ�� 
		/// </summary>
		void Update() override;

	private:
		size_t lastEntityID = 0;
		std::vector<Entity*> entities;

	};
}

