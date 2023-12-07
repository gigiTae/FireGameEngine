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

#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::Transform)
BEGIN_REFLECTION(Fire::Component::Transform)
MEMBER_REFLECTION(position)
MEMBER_REFLECTION(rotation)
MEMBER_REFLECTION(scale)
END_REFLECTION()

#endif