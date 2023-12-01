#pragma once

#include <string>

namespace Fire
{
	namespace Reflect
	{

		struct TypeDescriptor
		{
			std::string_view name;
			size_t size;

			TypeDescriptor(std::string_view name, size_t size)
				:name{ name }, size{ size } {}

			virtual ~TypeDescriptor() {}
			virtual const std::string_view& GetFullName() const { return name; }
			virtual void Write(const void* obj, std::string& data, int indentLevel = 0) const = 0;
		};

	}
}