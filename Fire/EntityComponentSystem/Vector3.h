#pragma once

#include <string>
#include "ReflectionHeader.h"

namespace Fire
{
	namespace Component
	{
		struct Vector3
		{
			float x;
			float y;
			float z;
		};
	}
}

REFLECT_CHECK(Fire::Component::Vector3)
