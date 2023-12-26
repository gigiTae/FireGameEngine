//#include <iostream>
//#include "../ImpReflection/ImpReflectionHeader.h"
//#include "../EngineModule/EngineModuleHeader.h"
//
//namespace example
//{
//	enum class Color
//	{
//		Red,
//		Blue,
//		Green,
//	};
//
//}
//
//REFLECTION_ENUM_BEGIN(example::Color)
//REFLECTION_ENUM_MEMBER(Red)
//REFLECTION_ENUM_MEMBER(Blue)
//REFLECTION_ENUM_MEMBER(Green)
//REFLECTION_ENUM_END()
//
//class InternalValue
//{
//public:
//	float high = 3.141592f;
//	float gravity = 10.f;
//	example::Color color = example::Color::Blue;
//};
//
//REFLECTION_BEGIN(InternalValue)
//REFLECTION_MEMBER(high)
//REFLECTION_MEMBER(color)
//REFLECTION_MEMBER(gravity)
//REFLECTION_END()
//
//class Mesh : public ImpEngineModule::Component
//{
//	InternalValue internalValue;
//	example::Color color;
//	example::Color baseColor;
//	example::Color normal;
//	float bobo;
//
//	REFLECTION_FRIEND(Mesh)
//};
//
//REFLECTION_BEGIN(Mesh)
//REFLECTION_MEMBER(internalValue)
//REFLECTION_MEMBER(bobo)
//REFLECTION_MEMBER(baseColor)
//REFLECTION_MEMBER(normal)
//REFLECTION_MEMBER(color)
//REFLECTION_END()
//
//int main()
//{
//	using namespace ImpReflection;
//
//	Mesh mesh{};
//
//	Type* type = TypeConverter<Mesh>::Get();
//
//	std::string writeData{};
//
//	type->Write(&mesh, writeData, 0);
//
//	std::cout << writeData;
//
//	return 0;
//}