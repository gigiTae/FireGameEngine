#pragma once

namespace EngineModule 
{
	using TypeIndex = std::type_index;

	/// <summary>
	/// 타입에 해당하는 TypeIndex를 반환한다.
	/// </summary>
	template <typename T>
	TypeIndex GetTypeIndex()
	{
		static TypeIndex index = std::type_index(typeid(T));
		return index;
	}
}
