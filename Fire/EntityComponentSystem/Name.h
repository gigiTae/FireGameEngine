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

REFLECT_CHECK(Fire::Component::Name)

