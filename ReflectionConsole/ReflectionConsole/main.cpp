#include <iostream>
#include "../ImpReflection/ImpReflectionHeader.h"

// ���÷����� Ŭ���� 
struct Data
{
	float length = 10.f;
	int index = 5;
	std::string name = "�̱���";
};

// ���÷��� ��ũ�� 
REFLECTION_BEGIN(Data)
REFLECTION_MEMBER(length)
REFLECTION_MEMBER(index)
REFLECTION_MEMBER(name)
REFLECTION_END()

int main()
{
	Data data;

	// Data Ÿ�Կ� ���� ������ �����´�
	ImpReflection::Type * type = ImpReflection::TypeConverter<Data>::Get();
	std::string text;

	// ����� Ÿ���� ������ ������ text�� �����.
	type->Write(&data, text);

	std::cout << text;

	return 0;
}