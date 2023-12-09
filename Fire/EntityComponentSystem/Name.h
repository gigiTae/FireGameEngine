#pragma once

#include <string>
#include "../EntityComponentSystem/ReflectionHeader.h"
#include "OBJECT_TYPE.h"
#include "Transform.h"

namespace Fire
{
	namespace Component
	{
		struct Name
		{
			std::string name;
			OBJECT_TYPE category;

			DECLARE_FREIND_WITH_REFECTION(Name)
		};
	}
}

#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::Name)
BEGIN_REFLECTION(Fire::Component::Name)
MEMBER_REFLECTION(name)
MEMBER_REFLECTION(category)
END_REFLECTION()

#endif