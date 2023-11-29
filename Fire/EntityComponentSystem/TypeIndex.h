#pragma once

/// RTTI »ç¿ë
#include <typeindex>
#include <typeinfo>

using TypeIndex = std::type_index;

template <typename ComponentType>
TypeIndex GetTypeIndex()
{
	return std::type_index(typeid(ComponentType));
}