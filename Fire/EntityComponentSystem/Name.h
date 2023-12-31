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
			std::vector<int> vecI;

			DECLARE_FREIND_WITH_REFECTION(Name)
		};
	}
}