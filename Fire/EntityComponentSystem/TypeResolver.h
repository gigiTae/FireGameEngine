#pragma once

#include "ITypeResolver.h"
#include "TypeCheck.h"
#include "ReflectCheck.h"

namespace Fire
{
	namespace Reflect
	{
		struct TypeDescriptor;

		template <typename T>
		struct  TypeResolver : public ITypeResolver
		{
			static TypeDescriptor* Get()
			{
				if constexpr (ReflectCheck<T>::IsReflect)
				{
					return &ReflectCheck<T>::Reflection;
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