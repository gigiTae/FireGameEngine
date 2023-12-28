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

// 매크로해석하면 아래의 모양이 나온다.

// 템플릿 클래스의 특수화
template<>
class ImpReflection::Meta<Monster>
{
public:
	// 리플렉션 여부를 판단하는 변수
	constexpr static bool IsReflect = true;
	
	// 리플렉션 정보를 초기화하기위해서 클래스 정적변수의 초기화를 사용한다.
	static class ImpReflection::ClassType _type;
	
	// 초기화를 위한 정적 멤버 함수 
	static void Initialize(ImpReflection::ClassType*);
};

// ImpReflection::Meta<int>::IsReflect = false; -> 특수화하지 않은 경우

// ImpReflection::Meta<Monster>::IsReflect = true; -> 특수화한 경우

// 클래스 정적변수 초기화
ImpReflection::ClassType ImpReflection::Meta<Monster>::_type
{
	// 정적변수를 초기화하는 과정에서 인자로 초기화 함수를 받는다.
	ImpReflection::Meta<Monster>::Initialize
};

// 초기화를 위한 정적 멤버 함수 구현
void ImpReflection::Meta<Monster>::Initialize(ImpReflection::ClassType* classType)
{
	using T = Monster;

	// 클래스의 정보를 전달한다. 타입의 카테고리, 클래스이름, 클래스의 사이즈, 클래스의 메모리할당 등등
	classType->Set(TypeCategory::Class, "Monster", sizeof(T), []()->void* {return new T(); }, Tag::Default);

	// 싱글톤으로 구현된 타입의 정보를 저장하는 매니져이다. 실행시간에 타입의 정보들에 접근하기 위해서
	// 싱글톤 패턴을 사용하였다.
	TypeManager::GetInstance()->AddTypeInfomation("Monster", { std::type_index{typeid(T)},classType });
	
	// 클래스 타입은 멤버변수를 가지로 있으므로 멤버변수의 대한 정보를 전달한다.
	//  변수명, 클래스와 변수의 메모리오프셋, 해당하는 타입의 리플렉션 정보 등등
	classType->_members.push_back(ImpReflection::ClassType::Member
		{"hp", offsetof(T, hp), ImpReflection::TypeConverter<decltype(T::hp)>::Get()});
	
	classType->_members.push_back(ImpReflection::ClassType::Member
	{"level", offsetof(T, level), ImpReflection::TypeConverter<decltype(T::level)>::Get()});
}

