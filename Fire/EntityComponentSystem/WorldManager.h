#pragma once

#include <string>

namespace Fire
{
	namespace ECS
	{
		class World;
	}

	namespace Manager
	{

		class WorldManager
		{
		public:
			WorldManager();
			~WorldManager();

			void SaveWorldData(Fire::ECS::World* world, const std::string& filePath);
			void LoadWorldData(Fire::ECS::World* world, const std::string& filePath);

		};
	}
}

