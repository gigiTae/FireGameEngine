#pragma once

#include <string>
#include "../Reflection/ReflectionHeader.h"
#include "OBJECT_TYPE.h"

namespace Fire
{
	namespace Component
	{
		struct Name
		{
			std::string name;
			bool isConst;
			OBJECT_TYPE category;
		};
	}
}

BEGIN_REFLECTION(Fire::Component::Name)
MEMBER_REFLECTION(name)
MEMBER_REFLECTION(isConst)
MEMBER_REFLECTION(category)
END_REFLECTION()

