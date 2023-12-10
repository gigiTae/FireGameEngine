#pragma once


#include "../EntityComponentSystem/ReflectionHeader.h"

namespace Fire
{
	namespace Component
	{
		struct SphereMesh
		{
			float r;
			float g;
			float b;
			float a;
		};
	}

}


#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::SphereMesh)
BEGIN_REFLECTION(Fire::Component::SphereMesh)
MEMBER_REFLECTION(r)
MEMBER_REFLECTION(g)
MEMBER_REFLECTION(b)
MEMBER_REFLECTION(a)
END_REFLECTION()

#endif