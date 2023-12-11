#pragma once
#include "BaseSystem.h"

namespace ImpEngineModule
{
	/// <summary>
	/// Componentó�� �ý��۵��� System�� ��� �޾Ƽ� �����Ѵ�.
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