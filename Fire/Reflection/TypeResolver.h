#pragma once

#include "ITypeResolver.h"
#include "TypeCheck.h"

namespace Fire
{
	namespace Reflect
	{
		struct ITypeDescriptor;

		template <typename T>
		struct  TypeResolver : public ITypeResolver
		{
			static ITypeDescriptor* Get()
			{
				if constexpr (Check<T>::IsReflected)
				{
					return &T::Reflection;
				}
				else
				{
					ITypeDescriptor* desc = GetPrimitiveDescriptor<T>();
					return desc;
				}
			}

		};


	}
}