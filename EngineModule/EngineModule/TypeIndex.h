#pragma once

namespace EngineModule 
{
	using TypeIndex = std::type_index;

	template <typename T>
	TypeIndex GetTypeIndex()
	{
		static TypeIndex index = std::type_index(typeid(T));
		return index;
	}
}
