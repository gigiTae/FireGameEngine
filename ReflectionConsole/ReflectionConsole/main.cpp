#include <iostream>
#include "../ImpReflection/ImpReflectionHeader.h"

// 리플렉션할 클래스 
struct Data
{
	float length = 10.f;
	int index = 5;
	std::string name = "이기태";
};

// 리플렉션 매크로 
REFLECTION_BEGIN(Data)
REFLECTION_MEMBER(length)
REFLECTION_MEMBER(index)
REFLECTION_MEMBER(name)
REFLECTION_END()

int main()
{
	Data data;

	// Data 타입에 대한 정보를 가져온다
	ImpReflection::Type * type = ImpReflection::TypeConverter<Data>::Get();
	std::string text;

	// 저장된 타입의 정보를 가지고 text로 만든다.
	type->Write(&data, text);

	std::cout << text;

	return 0;
}