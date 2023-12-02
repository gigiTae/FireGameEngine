#include <iostream> 
#include "ReflectionHeader.h"
#include <vector>
#include "compoent.h"

int main()
{
	Tmp tmp{ {"원영","장원"}, };

	Fire::Reflect::ITypeDescriptor* desc = Fire::Reflect::TypeResolver<Tmp>::Get();

	auto typeMap = Fire::Reflect::TypeMap::GetTypeMap();

	std::string parsingData1{};
	desc->Write(&tmp, parsingData1);

	Position pos{ 1.f,2.f,67.f };
	Fire::Reflect::ITypeDescriptor* desc2 = Fire::Reflect::TypeResolver<Position>::Get();
	
	desc2->Write(&pos, parsingData1);
	
	std::cout << parsingData1;



	return 0;
}
