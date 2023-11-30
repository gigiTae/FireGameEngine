
#include "Reflect.h"

namespace Fire
{

	namespace Reflect
	{
		/// <summary>
		/// A type descriptor for int
		/// </summary>
		struct TypeDescriptor_Int : TypeDescriptor
		{
			TypeDescriptor_Int() : TypeDescriptor("int", sizeof(int)){}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "int{";
				const int* val = (const int*)obj;
				data += std::to_string(*val);
				data += "}";
			}
		};

		template <>
		TypeDescriptor* GetPrimitiveDescriptor<int>()
		{
			static TypeDescriptor_Int typeDesc;
			return &typeDesc;
		}
	}

}