#include <iostream> 
#include "ReflectionHeader.h"
#include <vector>
#include <locale>

struct Tmp
{
	std::vector<std::string> key;

	REFLECT();
};


int main()
{
	std::wcout.imbue(std::locale(""));
	Tmp tmp{ {"원영","장원"},};

	Fire::Reflect::ITypeDescriptor* desc = Fire::Reflect::TypeResolver<Tmp>::Get();

	auto typeMap = Fire::Reflect::TypeMap::GetTypeMap();

	std::string parsingData1{};
	desc->Write(&tmp, parsingData1);
	desc->Read(&tmp, parsingData1,0,parsingData1.size());

	std::cout << parsingData1;
	
	
	return 0;
}

REFLECT_STRUCT_BEGIN(Tmp)
REFLECT_STRUCT_MEMBER(key)
REFLECT_STRUCT_END() 