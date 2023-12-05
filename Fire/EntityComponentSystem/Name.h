#pragma once

#include <string>
#include "../Reflection/Macro.h"

namespace Fire
{
	namespace Component
	{
		struct Name
		{
			std::string name;
	
		};

	}
}

BEGIN_REFLECTION(Fire::Component::Name)
MEMBER_REFLECTION(name)
END_REFLECTION()
