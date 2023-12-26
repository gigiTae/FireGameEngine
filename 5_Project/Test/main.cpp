//#include <iostream>
//#include <map>
//#include <string>
//#include <type_traits>
//#include "../ImpReflection/ImpReflectionHeader.h"
//
//class Position
//{
//public:
//	std::unordered_map<std::string, float> map{ {"¾È³ç",1.f}, {"apple",2.f}};
//	std::list<int> list{ 1,2,3,4 };
//	std::vector<float> vec{1.f, 33.f, 0.3f};
//public:
//	REFLECTION_FRaIEND(Position)
//};
//
//REFLECTION_BEGIN(Position)
//REFLECTION_MEMBER_UNORDERED_MAP(map,std::string,float)
//REFLECTION_MEMBER(list)
//REFLECTION_MEMBER(vec)
//REFLECTION_END()
//
//
//int main()
//{
//	using namespace ImpReflection;
//
//	Position pos;
//
//	std::string data;
//	Type* type = TypeConverter<Position>::Get();
//
//	type->Write(&pos, data,0);
//
//	std::cout << data;
//
//
//	return 0;
//}