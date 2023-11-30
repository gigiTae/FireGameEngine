//#include <iostream>
//#include <fstream>
//#include "Reflect.h"
//
//
//struct Tmp
//{
//	int data;
//
//
//	REFLECT();
//	//static void Reflection(){}
//};
//
//
//int main()
//{
//	Tmp tmp{ 7657659 };
//	
//	Fire::Reflect::TypeDescriptor* desc = Fire::Reflect::TypeResolver<Tmp>::Get();
//	
//	std::string parsingData{};
//	desc->Write(&tmp, parsingData);
//
//	std::cout << parsingData;
//
//	return 0;
//
//}
//
//REFLECT_STRUCT_BEGIN(Tmp)
//REFLECT_STRUCT_MEMBER(data)
//REFLECT_STRUCT_END()