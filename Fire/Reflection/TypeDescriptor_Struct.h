#pragma once
#include <vector>
#include "ITypeDescriptor.h"
#include "StirngHelper.h"


namespace Fire
{
	namespace Reflect
	{
		struct TypeDescriptor_Struct : ITypeDescriptor
		{
			struct  Member
			{
				std::string_view name;
				size_t offset;
				ITypeDescriptor* type;
			};

			std::vector<Member> members;

			TypeDescriptor_Struct(void(*Init)(TypeDescriptor_Struct*))
				:ITypeDescriptor{ "",0 }
			{
				Init(this);
			}
			TypeDescriptor_Struct(std::string_view name, size_t size, const std::initializer_list<Member>& init)
				:ITypeDescriptor{ "",0 }, members{ init } {}

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

			void Read(void* obj, std::string& data, size_t begin, size_t end)const override
			{
				size_t open = StringHelper::FindOpeningBrace(data,begin);
				size_t close = StringHelper::FindClosingBrace(data,begin);

				for (const Member& member : members)
				{
					size_t memberOpen = StringHelper::FindOpeningBrace(data,open+1);
					size_t memberClose = StringHelper::FindClosingBrace(data, open+1);

					member.type->Read((char*)obj + member.offset, data, memberOpen+1, memberClose-1);
				
					open = memberClose + 1;
				}
			}
		};


	}
}
