#pragma once

#include <typeinfo>

#include "ITypeDescriptor.h"
#include "TypeCheck.h"
#include "TypeMap.h"


namespace Fire
{
	namespace Reflect
	{

		/// <summary>
		/// pointer
		/// </summary>
		template<typename T>
		struct TypeDescriptor_Pointer : ITypeDescriptor
		{
			TypeDescriptor_Pointer() :ITypeDescriptor( typeid(T).name(), sizeof(T)) 
			{
				name;
				int a = 0;
			}

			/// <summary>
			/// pointer can't write
			/// </summary>
			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */)const override
			{
				data += typeid(T).name();
				data += "{nullptr}";
			}

			void Read(void* obj, std::string& data, size_t begin, size_t end) const override
			{
				/// 포인터는 nullptr 초기화
				std::string sValue = data.substr(begin, end - begin);

				if (sValue == "nullptr")
					void* obj = nullptr;
				else
				{
					/// TODO : 다른형식의 포인터 초기화?
					/// ex) 객체를 생성한다던지? 
				}
			}
		};

		/// <summary>
		/// poiter 
		/// </summary>
		template <typename T>
		constexpr ITypeDescriptor* GetPrimitiveDescriptor<T*>()
		{
			static TypeDescriptor_Pointer<T> typeDesc;
			TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
			return &typeDesc;
		}


		/// <summary>
		/// int
		/// </summary>
		struct TypeDescriptor_Int : ITypeDescriptor
		{
			TypeDescriptor_Int() : ITypeDescriptor("int", sizeof(int)) {}

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
		/// int
		/// </summary>
		template <>
		ITypeDescriptor* GetPrimitiveDescriptor<int>()
		{
			static TypeDescriptor_Int typeDesc;
			TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);

			return &typeDesc;
		}

		/// <summary>
		/// float
		/// </summary>
		struct TypeDescriptor_Float : ITypeDescriptor
		{
			TypeDescriptor_Float() :ITypeDescriptor("float", sizeof(float)) {}

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
		/// float
		/// </summary>
		template <>
		ITypeDescriptor* GetPrimitiveDescriptor<float>()
		{
			static TypeDescriptor_Float typeDesc;
			TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
			return &typeDesc;
		}

		/// <summary>
		/// double
		/// </summary>
		struct TypeDescriptor_Double :ITypeDescriptor
		{
			TypeDescriptor_Double() :ITypeDescriptor("double", sizeof(double)) {}

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
		/// double
		/// </summary>
		template<>
		ITypeDescriptor* GetPrimitiveDescriptor<double>()
		{
			static TypeDescriptor_Double typeDesc;
			TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
			return &typeDesc;
		}
	}
}

