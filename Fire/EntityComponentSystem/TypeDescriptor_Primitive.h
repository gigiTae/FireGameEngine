#pragma once

#include <typeinfo>

#include "TypeDescriptor.h"
#include "TypeCheck.h"
#include "TypeMap.h"


namespace Fire
{
	namespace Reflect
	{

		/// <summary>
		/// pointer
		/// </summary>
		//template<typename T>
		//struct TypeDescriptor_Pointer : TypeDescriptor
		//{
		//	TypeDescriptor_Pointer() :TypeDescriptor(typeid(T).name(), sizeof(T))
		//	{
		//		name;
		//		int a = 0;
		//	}

		//	/// <summary>
		//	/// pointer can't write
		//	/// </summary>
		//	void Write(const void* obj, std::string& data, int indentLevel /* = 0 */)const override
		//	{
		//		data += typeid(T).name();
		//		data += "{nullptr}";
		//	}

		//	void Read(void* obj, std::string& data, size_t begin, size_t end) const override
		//	{
		//		/// 포인터는 nullptr 초기화
		//		std::string sValue = data.substr(begin, end - begin);

		//		if (sValue == "nullptr")
		//			void* obj = nullptr;
		//		else
		//		{
		//			/// TODO : 다른형식의 포인터 초기화?
		//			/// ex) 객체를 생성한다던지? 
		//		}
		//	}
		//};

		/// <summary>
		/// int
		/// </summary>
		struct TypeDescriptor_Int : TypeDescriptor
		{
			TypeDescriptor_Int() : TypeDescriptor("int", sizeof(int), TYPE_CATEGORY::PRIMITIVE) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "int{";
				const int* val = (const int*)obj;
				data += std::to_string(*val);
				data += "}";
			}

			void Read(void* obj, std::string& data, size_t begin, size_t end) const override
			{
				std::string sValue = data.substr(begin, end - begin);

				int iValue = std::stoi(sValue);

				int* iObj = reinterpret_cast<int*>(obj);
				*iObj = iValue;
			}
		};


		/// <summary>
		/// float
		/// </summary>
		struct TypeDescriptor_Float : TypeDescriptor
		{
			TypeDescriptor_Float() :TypeDescriptor("float", sizeof(float), TYPE_CATEGORY::PRIMITIVE) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "float{";
				const float* val = (const float*)obj;
				data += std::to_string(*val);
				data += "}";
			}

			void Read(void* obj, std::string& data, size_t begin, size_t end) const override
			{
				std::string sValue = data.substr(begin, end - begin);

				float fValue = std::stof(sValue);

				float* fObj = reinterpret_cast<float*>(obj);
				*fObj = fValue;
			}
		};


		/// <summary>
		/// double
		/// </summary>
		struct TypeDescriptor_Double :TypeDescriptor
		{
			TypeDescriptor_Double() :TypeDescriptor("double", sizeof(double), TYPE_CATEGORY::PRIMITIVE) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "double{";
				const double* val = (const double*)obj;
				data += std::to_string(*val);
				data += "}";
			}

			void Read(void* obj, std::string& data, size_t begin, size_t end) const override
			{
				std::string sValue = data.substr(begin, end - begin);

				double dValue = std::stod(sValue);

				double* dObj = reinterpret_cast<double*>(obj);
				*dObj = dValue;
			}
		};


		/// <summary>
		/// bool
		/// </summary>
		struct TypeDescriptor_Bool :TypeDescriptor
		{
			TypeDescriptor_Bool() :TypeDescriptor("bool", sizeof(bool), TYPE_CATEGORY::PRIMITIVE) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "bool{";
				const bool* val = (const bool*)obj;
				if (*val)
				{
					data += '1';
				}
				else
				{
					data += '0';
				}
				data += "}";
			}

			void Read(void* obj, std::string& data, size_t begin, size_t end) const override
			{
				std::string sValue = data.substr(begin, end - begin);
				bool* dObj = reinterpret_cast<bool*>(obj);

				if (sValue.c_str() == "0")
					*dObj  = false;
				else
					*dObj = true;
			}
		};


	}
}

