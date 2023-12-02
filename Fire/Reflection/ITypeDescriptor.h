#pragma once

#include <string>

namespace Fire
{
	namespace Reflect
	{
	
		struct ITypeDescriptor
		{
			std::string_view name;
			size_t size;

			ITypeDescriptor(std::string_view name, size_t size)
				:name{ name }, size{ size } {}

			virtual ~ITypeDescriptor() {}
			virtual std::string GetFullName() const { return std::string(name); }
			virtual void Write(const void* obj, std::string& data, int indentLevel = 0) const = 0;
			virtual void Read(void* obj, std::string& data, size_t begin, size_t end)const {};

		};

	}
}
