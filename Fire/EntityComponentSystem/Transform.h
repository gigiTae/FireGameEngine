#pragma once

#include "ReflectionHeader.h"
#include "Vector3.h"

namespace Fire
{
	namespace Component
	{
		struct Transform
		{
			Fire::Component::Vector3 position;
			Fire::Component::Vector3 rotation;
			Fire::Component::Vector3 scale;
		};
	}
}

REFLECT_CHECK(Fire::Component::Transform)