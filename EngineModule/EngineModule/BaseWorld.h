#pragma once



namespace EngineModule
{
	class Entity;

	/// <summary>
	/// World의 추상클래스
	/// </summary>
	class BaseWorld
	{
	public:
		virtual ~BaseWorld() {}

		virtual Entity* CreateEntity() abstract;

		virtual void DestroyEntity(Entity* ent, bool immediate = false) abstract;

		virtual void DestroyEntity(size_t id, bool immediate= false) abstract;

		virtual Entity* GetEntity(size_t id)const abstract;

		virtual Entity* GetEntity(const std::string& name)const abstract;

		virtual void Reset() abstract;

		virtual void Start() abstract;

		virtual void Update() abstract;
	};

}