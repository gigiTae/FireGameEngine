#pragma once
#include <typeinfo>

#include "TypeDescriptor.h"
#include "TypeCheck.h"

#include <codecvt>
#include <Windows.h>

namespace Fire
{
	namespace Reflect
	{
		/// <summary>
		/// string
		/// </summary>
		struct TypeDescriptor_StdString :
			public TypeDescriptor
		{
			TypeDescriptor_StdString() : TypeDescriptor("std::string", sizeof(int)) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "std::string{";
				const std::string* val = (const std::string*)obj;
				data += *val;
				data += "}";
			}

		};

		/// <summary>
		/// string
		/// </summary>
		template <>
		TypeDescriptor* GetPrimitiveDescriptor<std::string>()
		{
			static TypeDescriptor_StdString typeDesc;
			return &typeDesc;
		}

		/// <summary>
		/// wstring
		/// </summary>
		struct TypeDescriptor_StdWstring :
			public TypeDescriptor
		{
			TypeDescriptor_StdWstring() : TypeDescriptor("std::wstring", sizeof(int)) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "std::wstring{";

				// binary data∑Œ ¿˙¿Â
				const std::wstring* tmp = reinterpret_cast<const std::wstring*>(obj);
				const wchar_t* tmp2 = tmp->c_str();
				std::string tmp3(reinterpret_cast<const char*>(tmp2), tmp->size());

				data += tmp3;
				
				data += "}";
			}

		};

		/// <summary>
		/// wstring
		/// </summary>
		template <>
		TypeDescriptor* GetPrimitiveDescriptor<std::wstring>()
		{
			static TypeDescriptor_StdWstring typeDesc;
			return &typeDesc;
		}


	}
}
