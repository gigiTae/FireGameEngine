//#include <iostream>
//
//#include "../ImpReflection/ImpReflectionHeader.h"
//
//class Position
//{
//	float x;
//	float y;
//	float z;
//
//public:
//	REFLECTION_FRIEND(Position);
//};
//
//REFLECTION_BEGIN(Position)
//REFLECTION_MEMBER(x)
//REFLECTION_MEMBER(y)
//REFLECTION_MEMBER(z)
//REFLECTION_END()
//
//class Rotation
//{
//	float x;
//	float y;
//	float z;
//
//public:
//	REFLECTION_FRIEND(Rotation);
//};
//
//REFLECTION_BEGIN(Rotation)
//REFLECTION_MEMBER(x)
//REFLECTION_MEMBER(y)
//REFLECTION_MEMBER(z)
//REFLECTION_END()
//
//class Scale
//{
//public:
//	float x;
//	float y;
//	float z;
//
//};
//
//REFLECTION_BEGIN(Scale)
//REFLECTION_MEMBER(x)
//REFLECTION_MEMBER(y)
//REFLECTION_MEMBER(z)
//REFLECTION_END()
//
//class Trasform
//{
//public:
//	Position pos;
//	Rotation rot;
//	Scale scale;
//};
//
//REFLECTION_BEGIN(Trasform)
//REFLECTION_MEMBER(pos)
//REFLECTION_MEMBER(rot)
//REFLECTION_MEMBER(scale)
//REFLECTION_END()
//
//
//int main()
//{
//	using namespace ImpReflection;
//
//	Type* type = TypeConverter<Position>::Get();
//
//	ClassType* classType = dynamic_cast<ClassType*>(type);
//
//	auto& members = classType->GetMembers();
//
//	std::cout << classType->GetFullName() << "ÀÇ ¸â¹öº¯¼ö Á¤º¸\n";
//	for (auto& member : members)
//	{
//		std::cout << "¸â¹öÀÌ¸§ : " << member._name << '\n';
//		std::cout << "¸â¹ö ¿ÀÇÁ¼Â : " << member._offset << '\n';
//		std::cout << "¸â¹ö Å¸ÀÔ : " << member._type->GetFullName() << "\n\n";
//	}
//
//
//	return 0;
//}