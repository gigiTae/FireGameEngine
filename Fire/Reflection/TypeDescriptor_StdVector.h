#pragma once
#include "TypeDescriptor.h"
#include "TypeResolver.h"
#include <vector>

namespace Fire
{
	namespace Reflect
	{
		struct TypeDescriptor_StdVector :
			public TypeDescriptor
		{
			TypeDescriptor* itemType;
			size_t(*GetSize)(const void*);
			const void* (*GetItem)(const void*, size_t);

			template <typename ItemType>
			TypeDescriptor_StdVector(ItemType*)
				:TypeDescriptor{ "std::vector<>",sizeof(std::vector<ItemType>) },
				itemType{ TypeResolver<ItemType>::Get() }
			{
				GetSize = [](const void* vecPtr)->size_t
					{
						const auto& vec = *(const std::vector<ItemType>*)vecPtr;
						return vec.size();
					};

				GetItem = [](const void* vecPtr, size_t index) -> const void*
					{
						const auto& vec = *(const std::vector<ItemType>*) vecPtr;
						return &vec[index];
					};
			}

			std::string GetFullName() const override
			{
				std::string tmp = std::string("std::vector<");
				tmp += itemType->GetFullName();
				tmp += ">";

				return tmp;
			}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				size_t vecSize = GetSize(obj);
				
				data += GetFullName();

				if (vecSize == 0)
				{
					data += {};
				}
				else
				{
					data += "{\n";
					for (size_t i = 0; i < vecSize; ++i)
					{
						data += std::string(4 * (indentLevel + 1), ' ');
						data += "[" + std::to_string(i) + "] ";
						itemType->Write(GetItem(obj, i), data, indentLevel + 1);
						data += '\n';
					}
					data += std::string(4 * indentLevel, ' ') + '}';
				}
			}


		};


	}
}

