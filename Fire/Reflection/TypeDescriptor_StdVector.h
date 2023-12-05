#pragma once
#include <assert.h>
#include <vector>

#include "TypeDescriptor.h"
#include "TypeResolver.h"
#include "StirngHelper.h"

namespace Fire
{
	namespace Reflect
	{
		template<typename T>
		struct TypeDescriptor_StdVector :
			public TypeDescriptor
		{
			TypeDescriptor* itemType;
			size_t(*GetSize)(const void*);
			const void* (*GetItem)(const void*, size_t);

			template <typename ItemType>
			TypeDescriptor_StdVector(ItemType*)
				:TypeDescriptor{ "std::vector<>",sizeof(std::vector<ItemType>),TYPE_CATEGORY::PRIMITIVE },
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
					data += "{}";
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

			void Read(void* obj, std::string& data, size_t begin, size_t end) const override
			{
				std::string subData = data.substr(begin, end - begin);
				
				std::vector<T>* vec = reinterpret_cast<std::vector<T>*>(obj);
				
				// 기본 생성자 호출해서 vector의 구현을 모르므로 초기화한다.
				*vec = std::vector<T>(); 
				vec->clear();

				// {} : vector 내부가 없다.
				if (begin == end)
				{
					return;
				}
				else // 멤버 변수를 추가한다.
				{
					int currentIndex = 0;
					size_t start = begin;

					while (true)
					{
						char c = data[start];

					    size_t index = StringHelper::FindIndex(data, start);
						if(index == std::string::npos)
							break;

						size_t open = StringHelper::FindOpeningBrace(data, start);
						size_t close = StringHelper::FindClosingBrace(data, start);

						T member; // 초기화하지않는다.

						itemType->Read((char*)&member, data, open+1,close-1);
						vec->push_back(member);
						
						++currentIndex;
						start = close + 1;
					}
				}
			}
		};


	}
}

