#pragma once

#include <type_traits>

namespace Fire
{
	namespace Reflect
	{
		struct ITypeDescriptor;

		template<typename T>
		constexpr ITypeDescriptor* GetPrimitiveDescriptor();

		//template <typename T, typename = void>
		//struct Check
		//{
		//	static constexpr bool IsReflected = false;
		//};

		//template <typename T>
		//struct Check<T, std::void_t<decltype(&T::Reflection)>>
		//{
		//	static constexpr bool IsReflected = true;
		//};

	}
}
