#pragma once

#include "ITypeResolver.h"
#include "TypeCheck.h"
#include "ReflectCheck.h"

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
				if constexpr (ReflectCheck<T>::IsReflect)
				{
					return &ReflectCheck<T>::Reflection;
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