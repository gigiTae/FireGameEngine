#include <iostream> 
#include "ReflectionHeader.h"


enum class COLOR
{
	RED,
	BLUE,
	BLACK,
};

BEGIN_REFLECTION_ENUM(COLOR)
ENUM_MEMBER_REFLECTION(RED)
ENUM_MEMBER_REFLECTION(BLUE)
ENUM_MEMBER_REFLECTION(BLACK)
END_REFLECTION_ENUM()

struct Player
{
	float speed;
	float hp;

};

BEGIN_REFLECTION(Player)
MEMBER_REFLECTION(speed)
MEMBER_REFLECTION(hp)
END_REFLECTION()


int main()
{

	auto map = Fire::Reflect::TypeMap::GetTypeMap();

	auto name = Fire::Reflect::TypeResolver<COLOR>::Get();

	auto desc = Fire::Reflect::ReflectCheck<COLOR>::Reflection;
	auto enu = desc.GetValueForName("BLUE");

	return 0;
}
