#pragma once
#include <typeinfo>

#include "TypeDescriptor.h"
#include "TypeCheck.h"
#include "TypeMap.h"

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
			TypeDescriptor_StdString() : TypeDescriptor("std::string", sizeof(std::string),TYPE_CATEGORY::PRIMITIVE) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "std::string{";
				const std::string* val = (const std::string*)obj;
				data += *val;
				data += "}";
			}

			void Read(void* obj, std::string& data, size_t begin, size_t end)const override
			{
				std::string str = data.substr(begin, end - begin);
				
				std::string value = str;

				std::string* strObj = reinterpret_cast<std::string*>(obj);
				*strObj = value;
			}

		};



		/// <summary>
		/// wstring
		/// </summary>
		struct TypeDescriptor_StdWstring :
			public TypeDescriptor
		{
			TypeDescriptor_StdWstring() : TypeDescriptor("std::wstring", sizeof(std::wstring), TYPE_CATEGORY::PRIMITIVE) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "std::wstring{";

				const std::wstring* tmp = reinterpret_cast<const std::wstring*>(obj);
				for (wchar_t ch : *tmp) {
					data.push_back(static_cast<char>(ch & 0xFF));  // ���� �����ͷ� ����, ���ڵ��� ���� ������ ����
					data.push_back(static_cast<char>((ch >> 8) & 0xFF));
				}

				data += "}";
			}

			void Read(void* obj, std::string& data, size_t begin, size_t end)const override
			{ 
				std::wstring* strObj = reinterpret_cast<std::wstring*>(obj);
				strObj->clear();

				for (size_t i = begin; i < end; i += 2) {
					wchar_t ch = static_cast<unsigned char>(data[i]) | (static_cast<unsigned char>(data[i + 1]) << 8);
					strObj->push_back(ch);
				} 
			}
		};

		

	}
}
