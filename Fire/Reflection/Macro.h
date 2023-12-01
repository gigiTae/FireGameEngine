#pragma once

#define  REFLECT() \
		static struct Fire::Reflect::TypeDescriptor_Struct Reflection; \
		static void InitReflection(Fire::Reflect::TypeDescriptor_Struct*); 

#define REFLECT_STRUCT_BEGIN(type) \
		Fire::Reflect::TypeDescriptor_Struct type::Reflection{type::InitReflection};\
		void type::InitReflection(Fire::Reflect::TypeDescriptor_Struct* typeDesc) { \
			Fire::Reflect::TypeMap::Get()->AddType(#type,typeDesc); \
			using T = type; \
			typeDesc->name = #type; \
			typeDesc->size = sizeof(T); \
			typeDesc->members = {

#define REFLECT_STRUCT_MEMBER(name)\
			{#name, offsetof(T,name), Fire::Reflect::TypeResolver<decltype(T::name)>::Get()},

#define REFLECT_STRUCT_END() \
		}; \
	}
