#include <iostream>
#include "ReflectionHeader.h"


struct Tmp
{
	int data;
	double power = 1.34232;
	float speed = 2.4f;

	REFLECT();
};


int main()
{
	Tmp tmp{ 7657659 };

	Fire::Reflect::TypeDescriptor* desc = Fire::Reflect::TypeResolver<Tmp>::Get();

	std::string parsingData{};
	desc->Write(&tmp, parsingData);

	std::cout << parsingData;

	return 0;

}

REFLECT_STRUCT_BEGIN(Tmp)
REFLECT_STRUCT_MEMBER(data)
REFLECT_STRUCT_MEMBER(power)
REFLECT_STRUCT_MEMBER(speed)
REFLECT_STRUCT_END()