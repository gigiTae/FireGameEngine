#include <iostream> 
#include "ReflectionHeader.h"
#include <vector>
#include "compoent.h"


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


struct Tmp
{
	std::vector<std::string> key;

	int hp = 10;
	int mp = 200;
	int go = 10;

	std::vector<Position> monster;
};

BEGIN_REFLECTION(Tmp)
MEMBER_REFLECTION(key)
MEMBER_REFLECTION(hp)
MEMBER_REFLECTION(mp)
MEMBER_REFLECTION(go)
MEMBER_REFLECTION(monster)
END_REFLECTION()


int main()
{
	Tmp tmp{};

	Position p{ 1.f,2.f,3.f };

	tmp.monster.push_back(p);

	Fire::Reflect::ITypeDescriptor* desc = Fire::Reflect::TypeResolver<Tmp>::Get();

	auto typeMap = Fire::Reflect::TypeMap::GetTypeMap();

	std::string parsingData{};

	desc->Write(&tmp, parsingData);

	std::cout << parsingData;


	return 0;
}
