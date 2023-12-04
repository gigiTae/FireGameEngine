#pragma once

#include "ITypeDescriptor.h"
#include <string>
#include <assert.h>
#include <unordered_map>

namespace Fire
{
	namespace Reflect
	{

		template <typename ENUM_TYPE>
		struct TypeDescriptor_EnumClass : ITypeDescriptor
		{
		public:
			struct EnumInfo
			{
				ENUM_TYPE type;
				int castValue;
			};

		public:
			TypeDescriptor_EnumClass(void(*Init)(TypeDescriptor_EnumClass<ENUM_TYPE>*)) :ITypeDescriptor{ "",0 }
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

		private:
			std::unordered_map<std::string, EnumInfo> enumMembers;
		};


	}
}


