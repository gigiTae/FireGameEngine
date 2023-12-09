#pragma once

#include "ReflectionHeader.h"

namespace Fire
{
	namespace Component
	{
		class Player
		{
			int hp;
			int mp;
			int level;
			int attackPower;

			float height;

			DECLARE_FREIND_WITH_REFECTION(Player)
		};
	}

}

#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::Player)
BEGIN_REFLECTION(Fire::Component::Player)
MEMBER_REFLECTION(hp)
MEMBER_REFLECTION(mp)
MEMBER_REFLECTION(level)
MEMBER_REFLECTION(height)
END_REFLECTION()

#endif