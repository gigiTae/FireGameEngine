#pragma once

#include <type_traits>

namespace Fire
{
	namespace Reflect
	{
		struct TypeDescriptor;

		template<typename T>
		TypeDescriptor* GetPrimitiveDescriptor();

	}
}
