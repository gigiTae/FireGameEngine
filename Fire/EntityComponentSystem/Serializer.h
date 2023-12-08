#pragma once

#include "Entity.h"
#include "World.h"
#include "ReflectionHeader.h"
#include <filesystem>

namespace Fire
{
	namespace File
	{

		void LoadEntity(Fire::ECS::Entity* ent, const std::filesystem::path& path);
		void SaveEntity(Fire::ECS::Entity* ent, const std::filesystem::path& path);
	}
}
