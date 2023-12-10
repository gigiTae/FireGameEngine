#pragma once

#include "ReflectionHeader.h"
#include "Vector3.h"

namespace Fire
{
	namespace Component
	{
		struct Transform
		{
			Fire::Component::Vector3 position{ 0.f,0.f,0.f };
			Fire::Component::Vector3 rotation{ 0.f,0.f,0.f };
			Fire::Component::Vector3 scale{ 1.f,1.f,.1f };
		};
	}
}
