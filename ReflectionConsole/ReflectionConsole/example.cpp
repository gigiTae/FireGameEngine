#include "../ImpReflection/ImpReflectionHeader.h"


struct Monster
{
	int level;
	float hp;
};

// REFLECTION_BEGIN(Monster)
// REFLECTION_MEMBER(level)
// REFLECTION_MEMBER(hp)
// REFLECTION_END()

// ��ũ���ؼ��ϸ� �Ʒ��� ����� ���´�.

// ���ø� Ŭ������ Ư��ȭ
template<>
class ImpReflection::Meta<Monster>
{
public:
	// ���÷��� ���θ� �Ǵ��ϴ� ����
	constexpr static bool IsReflect = true;
	
	// ���÷��� ������ �ʱ�ȭ�ϱ����ؼ� Ŭ���� ���������� �ʱ�ȭ�� ����Ѵ�.
	static class ImpReflection::ClassType _type;
	
	// �ʱ�ȭ�� ���� ���� ��� �Լ� 
	static void Initialize(ImpReflection::ClassType*);
};

// ImpReflection::Meta<int>::IsReflect = false; -> Ư��ȭ���� ���� ���

// ImpReflection::Meta<Monster>::IsReflect = true; -> Ư��ȭ�� ���

// Ŭ���� �������� �ʱ�ȭ
ImpReflection::ClassType ImpReflection::Meta<Monster>::_type
{
	// ���������� �ʱ�ȭ�ϴ� �������� ���ڷ� �ʱ�ȭ �Լ��� �޴´�.
	ImpReflection::Meta<Monster>::Initialize
};

// �ʱ�ȭ�� ���� ���� ��� �Լ� ����
void ImpReflection::Meta<Monster>::Initialize(ImpReflection::ClassType* classType)
{
	using T = Monster;

	// Ŭ������ ������ �����Ѵ�. Ÿ���� ī�װ�, Ŭ�����̸�, Ŭ������ ������, Ŭ������ �޸��Ҵ� ���
	classType->Set(TypeCategory::Class, "Monster", sizeof(T), []()->void* {return new T(); }, Tag::Default);

	// �̱������� ������ Ÿ���� ������ �����ϴ� �Ŵ����̴�. ����ð��� Ÿ���� �����鿡 �����ϱ� ���ؼ�
	// �̱��� ������ ����Ͽ���.
	TypeManager::GetInstance()->AddTypeInfomation("Monster", { std::type_index{typeid(T)},classType });
	
	// Ŭ���� Ÿ���� ��������� ������ �����Ƿ� ��������� ���� ������ �����Ѵ�.
	//  ������, Ŭ������ ������ �޸𸮿�����, �ش��ϴ� Ÿ���� ���÷��� ���� ���
	classType->_members.push_back(ImpReflection::ClassType::Member
		{"hp", offsetof(T, hp), ImpReflection::TypeConverter<decltype(T::hp)>::Get()});
	
	classType->_members.push_back(ImpReflection::ClassType::Member
	{"level", offsetof(T, level), ImpReflection::TypeConverter<decltype(T::level)>::Get()});
}

