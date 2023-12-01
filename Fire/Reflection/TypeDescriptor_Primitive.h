#pragma once

#include <typeinfo>

#include "TypeDescriptor.h"
#include "TypeCheck.h"

#define STAR(A) #A

namespace Fire
{
	namespace Reflect
	{

		/// <summary>
		/// pointer
		/// </summary>
		template<typename T>
		struct TypeDescriptor_Pointer : TypeDescriptor
		{
			TypeDescriptor_Pointer() :TypeDescriptor( typeid(T).name(), sizeof(T)) {}

			/// <summary>
			/// pointer can't write
			/// </summary>
			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */)const override
			{
				data += typeid(T).name();
				data += "{nullptr}";
			}


		};

		/// <summary>
		/// poiter 
		/// </summary>
		template <typename T>
		constexpr TypeDescriptor* GetPrimitiveDescriptor<T*>()
		{
			static TypeDescriptor_Pointer<T> typeDesc;
			return &typeDesc;
		}


		/// <summary>
		/// int
		/// </summary>
		struct TypeDescriptor_Int : TypeDescriptor
		{
			TypeDescriptor_Int() : TypeDescriptor("int", sizeof(int)) {}

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
		TypeDescriptor* GetPrimitiveDescriptor<int>()
		{
			static TypeDescriptor_Int typeDesc;
			return &typeDesc;
		}

		/// <summary>
		/// float
		/// </summary>
		struct TypeDescriptor_Float : TypeDescriptor
		{
			TypeDescriptor_Float() :TypeDescriptor("float", sizeof(float)) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "float{";
				const float* val = (const float*)obj;
				data += std::to_string(*val);
				data += "}";
			}
		};

		/// <summary>
		/// float
		/// </summary>
		template <>
		TypeDescriptor* GetPrimitiveDescriptor<float>()
		{
			static TypeDescriptor_Float typeDesc;
			return &typeDesc;
		}

		/// <summary>
		/// double
		/// </summary>
		struct TypeDescriptor_Double :TypeDescriptor
		{
			TypeDescriptor_Double() :TypeDescriptor("double", sizeof(double)) {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += "double{";
				const double* val = (const double*)obj;
				data += std::to_string(*val);
				data += "}";
			}
		};

		/// <summary>
		/// double
		/// </summary>
		template<>
		TypeDescriptor* GetPrimitiveDescriptor<double>()
		{
			static TypeDescriptor_Double typeDesc;
			return &typeDesc;
		}
	}
}

