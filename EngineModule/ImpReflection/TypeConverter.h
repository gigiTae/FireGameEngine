#pragma once
#include "BaseTypeConverter.h"
#include "PrimitiveFunciton.h"
#include "Meta.h"

namespace ImpReflection
{
	class Type;

	/// <summary>
	/// T Ÿ�Կ� �ش��ϴ� Type�� ��ȯ�ϴ� HelperŬ����
	/// </summary>
	template <typename T>
	class TypeConverter :
		public BaseTypeConverter
	{
	public:
		static Type* Get()
		{
			if constexpr (Meta<T>::IsReflect)
			{
				return &Meta<T>::_type;
			}
			else
			{
				return GetPrimitiveType<T>();
			}
		}
	};


}