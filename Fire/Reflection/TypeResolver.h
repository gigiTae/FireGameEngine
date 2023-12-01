#pragma once

#include "TypeCheck.h"

namespace Fire
{
	namespace Reflect
	{
		struct TypeDescriptor;

		template <typename T>
		struct  TypeResolver
		{
			static TypeDescriptor* Get()
			{
				if constexpr (Check<T>::IsReflected)
				{
					return &T::Reflection;
				}
				else
				{
					TypeDescriptor* desc = GetPrimitiveDescriptor<T>();
					return desc;
				}
			}
		};


	}
}