#pragma once

namespace EngineModule 
{
	using TypeIndex = std::type_index;

	/// <summary>
	/// Ÿ�Կ� �ش��ϴ� TypeIndex�� ��ȯ�Ѵ�.
	/// </summary>
	template <typename T>
	TypeIndex GetTypeIndex()
	{
		static TypeIndex index = std::type_index(typeid(T));
		return index;
	}
}
