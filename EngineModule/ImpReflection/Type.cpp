#include "ImpReflectionPCH.h"
#include "Type.h"

ImpReflection::Type::Type(const std::string& name, size_t size, TypeCategory category)
	:_name(name), _size(size), _category(category)
{
}

const std::vector<ImpReflection::Type::EnumMember>& ImpReflection::Type::GetEnumMembers() const
{
	// 재정의 하지 않은 경우에는 빈컨테이너를 반환한다 
	static std::vector<ImpReflection::Type::EnumMember> vec;

	return vec;
}

void ImpReflection::Type::Set(TypeCategory category, const std::string& name,
	size_t size, std::function<void*()> func)
{
	_category = category;
	_name = name;
	_size = size;
	Get = func;
}
