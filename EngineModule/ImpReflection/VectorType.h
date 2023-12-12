#pragma once
#include "Type.h"

namespace ImpReflection
{
	/// <summary>
	/// std::vector
	/// </summary>
	
	template <typename T>
	class VectorType :
		public Type
	{
	public:
		Type* _itemType;
		size_t(*GetSize)(const void*);
		const void* (GetItem)(const void*, size_t);

		template <typename ItemType>

	};

}
