#pragma once

#include <vector>
#include "TypeResolver.h"
#include "TypeDescriptor_StdVector.h"

namespace Fire
{
	namespace Reflect
	{
		template <typename T>
		struct TypeResolver<std::vector<T>>
		{
			static TypeDescriptor* Get()
			{
				static TypeDescriptor_StdVector typeDesc{ (T*)nullptr };
				return &typeDesc;
			}

		};



	}
}