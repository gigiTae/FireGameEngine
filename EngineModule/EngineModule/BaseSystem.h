#pragma once


namespace ImpEngineModule
{
	class World;

	/// <summary>
	/// System Intetface
	/// </summary>
	class BaseSystem
	{
	public:
		virtual ~BaseSystem(){}

		virtual void Configure(ImpEngineModule::World* world) abstract;
		virtual void Unconfigure(ImpEngineModule::World* world)abstract;

		virtual void Update(ImpEngineModule::World* world, float dt) abstract;
	};
}
