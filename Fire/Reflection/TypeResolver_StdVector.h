#pragma once

#include <vector>
#include "TypeResolver.h"
#include "TypeDescriptor_StdVector.h"
#include "ITypeResolver.h"
#include "TypeMap.h"

namespace Fire
{
	namespace Reflect
	{
		struct ITypeDescriptor;

		template <typename T>
		struct TypeResolver<std::vector<T>> :public ITypeResolver
		{
			static ITypeDescriptor* Get()
			{
				static TypeDescriptor_StdVector<T> typeDesc{ (T*)nullptr };
				TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
				return &typeDesc;
			}
		};



	}
}