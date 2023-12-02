#pragma once
#include "ReflectionHeader.h"

struct Tmp
{
	std::vector<std::string> key;
	
	int hp = 10;
	int mp = 200;
	int go = 10;
};

BEGIN_REFLECTION(Tmp) 
MEMBER_REFLECTION(key)
MEMBER_REFLECTION(hp)
MEMBER_REFLECTION(mp)
MEMBER_REFLECTION(go)
END_REFLECTION()


struct Position
{
	float x;
	float y;
	float z;
};

BEGIN_REFLECTION(Position)
MEMBER_REFLECTION(x)
MEMBER_REFLECTION(y)
MEMBER_REFLECTION(z)
END_REFLECTION()