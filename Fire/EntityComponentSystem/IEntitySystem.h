#pragma once

namespace Fire
{
	namespace ECS
	{
		class World;

		class IEntitySystem
		{
		public:
			virtual ~IEntitySystem() {}
 
			virtual void Configure(World* world) {}

			virtual void Unconfigure(World* world) {}

			virtual void Tick(World* world, float dt) {}
		};
	}

}
