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
			bool isConst;
			OBJECT_TYPE category;
			Transform transform;
		};
	}
}

BEGIN_REFLECTION(Fire::Component::Name)
MEMBER_REFLECTION(name)
MEMBER_REFLECTION(isConst)
MEMBER_REFLECTION(category)
MEMBER_REFLECTION(transform)
END_REFLECTION()

