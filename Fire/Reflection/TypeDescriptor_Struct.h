#pragma once
#include "TypeDescriptor.h"
#include <vector>

namespace Fire
{
	namespace Reflect
	{
		struct TypeDescriptor_Struct : TypeDescriptor
		{
			struct  Member
			{
				std::string_view name;
				size_t offset;
				TypeDescriptor* type;
			};

			std::vector<Member> members;

			TypeDescriptor_Struct(void(*Init)(TypeDescriptor_Struct*))
				:TypeDescriptor{ "",0 }
			{
				Init(this);
			}
			TypeDescriptor_Struct(std::string_view name, size_t size, const std::initializer_list<Member>& init)
				:TypeDescriptor{ "",0 }, members{ init } {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += name;
				data += " {\n";
				for (const auto& member : members)
				{
					data += std::string(4 * (indentLevel + 1), ' ');
					data += member.name;
					data += " = ";
					member.type->Write((char*)obj + member.offset, data, indentLevel + 1);
					data += "\n";
				}
				data += std::string(4 * indentLevel, ' ') + "}";
			}
		};


	}
}
