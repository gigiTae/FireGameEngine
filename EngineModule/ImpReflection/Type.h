#pragma once

#include "BaseVariant.h"

namespace ImpReflect
{
	/// <summary>
	/// Type에 대한 정보들을 저장하는 클래스
	/// </summary>
	class Type
	{
	public:
		virtual ~Type(){}


	private:
		std::function<ImpReflect::BaseVariant()> GetVariant;
		TypeCategory _category = TypeCategory::None;
		std::string_view _name;
		size_t _size;
	};
}
