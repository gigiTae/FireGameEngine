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

#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::Vector3)
BEGIN_REFLECTION(Fire::Component::Vector3)
MEMBER_REFLECTION(x)
MEMBER_REFLECTION(y)
MEMBER_REFLECTION(z)
END_REFLECTION()

#endif