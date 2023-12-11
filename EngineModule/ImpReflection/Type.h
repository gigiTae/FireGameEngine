#pragma once

#include "BaseVariant.h"

namespace ImpReflect
{
	/// <summary>
	/// Type�� ���� �������� �����ϴ� Ŭ����
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
