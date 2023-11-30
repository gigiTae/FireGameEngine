#pragma once

#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

namespace Fire
{
	namespace Reflect
	{
		/// <summary>
		/// Base class of all type descritors
		/// </summary>
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


		/// <summary>
		/// Declare the function template that handles primitive types such as int, std::string, etc...
		/// 
		/// </summary>
		template<typename T>
		constexpr TypeDescriptor* GetPrimitiveDescriptor();

		/// <summary>
		/// C++ 17 
		/// 템플릿 특수화를 사용
		/// </summary>
		template <typename T, typename = void>
		struct Check
		{
			static constexpr bool IsReflected = false;
		};

		template <typename T>
		struct Check<T, std::void_t<decltype(&T::Reflection)>>
		{
			static constexpr bool IsReflected = true;
		};

		template <typename T>
		struct  TypeResolver
		{
			static TypeDescriptor* Get()
			{
				if constexpr (Check<T>::IsReflected)
				{
					return &T::Reflection;
				}
				else
				{
					return GetPrimitiveDescriptor<T>();
				}
			}
		};

		struct TypeDescriptor_Struct : TypeDescriptor
		{
			struct  Member
			{
				std::string_view name;
				size_t offset;
				TypeDescriptor* type;
			};

			std::vector<Member> members;

			TypeDescriptor_Struct(void(*Init)(TypeDescriptor_Struct*))
				:TypeDescriptor{"",0}
			{
				Init(this);
			}
			TypeDescriptor_Struct(std::string_view name, size_t size, const std::initializer_list<Member>& init)
				:TypeDescriptor{ "",0}, members{init} {}

			void Write(const void* obj, std::string& data, int indentLevel /* = 0 */) const override
			{
				data += name;
				data += " {\n";
				for (const auto& member : members)
				{
					data += std::string(4 * (indentLevel + 1), ' ');
					data += member.name;
					data += " = ";
					member.type->Write((char*)obj + member.offset, data, indentLevel + 1);
					data += "\n";
				}
				data += std::string(4 * indentLevel, ' ') + "}";
			}
		};

		


	}
}

#define  REFLECT() \
		static struct Fire::Reflect::TypeDescriptor_Struct Reflection; \
		static void InitReflection(Fire::Reflect::TypeDescriptor_Struct*); 

#define REFLECT_STRUCT_BEGIN(type) \
		Fire::Reflect::TypeDescriptor_Struct type::Reflection{type::InitReflection};\
		void type::InitReflection(Fire::Reflect::TypeDescriptor_Struct* typeDesc) { \
			using T = type; \
			typeDesc->name = #type; \
			typeDesc->size = sizeof(T); \
			typeDesc->members = {

#define REFLECT_STRUCT_MEMBER(name)\
			{#name, offsetof(T,name), Fire::Reflect::TypeResolver<decltype(T::name)>::Get()},

#define REFLECT_STRUCT_END() \
		}; \
	}
