#pragma once
#include "BaseTypeConverter.h"
#include "PrimitiveFunciton.h"
#include "Meta.h"

namespace ImpReflection
{
	class Type;

	/// <summary>
	/// T 타입에 해당하는 Type을 반환하는 Helper클래스
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