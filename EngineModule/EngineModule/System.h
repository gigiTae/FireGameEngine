#pragma once
#include "BaseSystem.h"

namespace ImpEngineModule
{
	/// <summary>
	/// Component처럼 시스템들은 System을 상속 받아서 구현한다.
	/// </summary>
	class System :
		public BaseSystem
	{
		friend class World;
	public:
		System();
		~System();

	public:
		void Configure(ImpEngineModule::World* world) override {};
		void Unconfigure(ImpEngineModule::World* world) override {};
		void Update(World* world, float dt) override {};

	private:
		bool _isEnable;
	};
}