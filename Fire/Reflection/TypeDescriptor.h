#pragma once

#include <string>
#include <vector>

namespace Fire
{
	namespace Reflect
	{
		enum class TYPE_CATEGORY
		{
			STRUCT,
			PRIMITIVE,
			ENUMCLASS,
			NONE,
		};

		struct TypeDescriptor
		{			
			TYPE_CATEGORY category = TYPE_CATEGORY::NONE;
			std::string_view name;
			size_t size;

			TypeDescriptor(std::string_view name, size_t size, TYPE_CATEGORY type)
				:name{ name }, size{ size } ,category(type)
			{
				type;
			}

			virtual ~TypeDescriptor() {}
			virtual std::string GetFullName() const { return std::string(name); }
			virtual void Write(const void* obj, std::string& data, int indentLevel = 0) const = 0;
			virtual void Read(void* obj, std::string& data, size_t begin, size_t end)const {};
			virtual std::vector<std::pair<std::string,int>> GetEnumMember()const 
			{
				return std::vector<std::pair<std::string, int>>();
			};
		};

	}
}
