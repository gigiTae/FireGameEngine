#pragma once

#include "TypeDescriptor.h"
#include <string>
#include <assert.h>
#include <unordered_map>

namespace Fire
{
	namespace Reflect
	{

		template <typename ENUM_TYPE>
		struct TypeDescriptor_EnumClass : TypeDescriptor
		{
		public:
			struct EnumInfo
			{
				ENUM_TYPE type;
				int castValue;
			};

		public:
			TypeDescriptor_EnumClass(void(*Init)(TypeDescriptor_EnumClass<ENUM_TYPE>*)) :TypeDescriptor{ "",0,TYPE_CATEGORY::ENUMCLASS }
			{
				Init(this);
			}
			~TypeDescriptor_EnumClass() {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{

			}

			void Read(void* obj, std::string& data, size_t begin, size_t end) const override
			{

			}

			void AddEnumMember(const std::string name, const TypeDescriptor_EnumClass::EnumInfo& info)
			{
				assert(enumMembers.find(name) == enumMembers.end());

				enumMembers.insert({ name,info });
			}

			ENUM_TYPE GetValueForName(const std::string& name)
			{
				auto iter = enumMembers.find(name);
				
				assert(iter != enumMembers.end());

				return iter->second.type;
			}

			std::vector<std::pair<std::string, int>> GetEnumMember()const  override;

		private:
			std::unordered_map<std::string, EnumInfo> enumMembers;
		};

		template <typename ENUM_TYPE>
		std::vector<std::pair<std::string, int>> Fire::Reflect::TypeDescriptor_EnumClass<ENUM_TYPE>::GetEnumMember() const
		{
			std::vector<std::pair<std::string, int>> vec;

			for (auto& member : enumMembers)
			{
				vec.push_back({ member.first,member.second.castValue });
			}

			return vec;
		}

	}
}


