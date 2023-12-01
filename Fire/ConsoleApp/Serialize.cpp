#include <iostream>
#include "ReflectionHeader.h"
#include <vector>

struct Tmp
{
	int data;
	int data2;
	int data3;

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
REFLECT_STRUCT_MEMBER(data2)
REFLECT_STRUCT_MEMBER(data3)
REFLECT_STRUCT_END()