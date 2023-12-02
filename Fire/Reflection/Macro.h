#pragma once


// My Reflection

#define REFLECT_CHECK(type)\
		template<>\
		class Fire::Reflect::ReflectCheck<type>\
		{\
		public:\
			constexpr static bool IsReflect = true;\
			static struct Fire::Reflect::TypeDescriptor_Struct Reflection;\
			static void InitReflection(Fire::Reflect::TypeDescriptor_Struct*);\
		};

#define BEGIN_REFLECTION(type)\
		REFLECT_CHECK(type)\
		Fire::Reflect::TypeDescriptor_Struct Fire::Reflect::ReflectCheck<type>::Reflection\
						{Fire::Reflect::ReflectCheck<type>::InitReflection};\
		void Fire::Reflect::ReflectCheck<type>::InitReflection(Fire::Reflect::TypeDescriptor_Struct* desc)\
			{\
				Fire::Reflect::TypeMap::GetTypeMap()->AddType(#type,desc);\
				using T = type; \
				desc->name = #type; \
				desc->size = sizeof(T); \
				desc->members = {
						
#define MEMBER_REFLECTION(name)\
			{#name, offsetof(T,name), Fire::Reflect::TypeResolver<decltype(T::name)>::Get()},

#define END_REFLECTION()\
		}; \
	}

// FlexibleReflection Define

//#define  REFLECT() \
//		static struct Fire::Reflect::TypeDescriptor_Struct Reflection; \
//		static void InitReflection(Fire::Reflect::TypeDescriptor_Struct*); 
//
//#define REFLECT_STRUCT_BEGIN(type) \
//		Fire::Reflect::TypeDescriptor_Struct type::Reflection{type::InitReflection};\
//		void type::InitReflection(Fire::Reflect::TypeDescriptor_Struct* typeDesc) { \
//			Fire::Reflect::TypeMap::GetTypeMap()->AddType(#type,typeDesc); \
//			using T = type; \
//			typeDesc->name = #type; \
//			typeDesc->size = sizeof(T); \
//			typeDesc->members = {
//
//#define REFLECT_STRUCT_MEMBER(name)\
//			{#name, offsetof(T,name), Fire::Reflect::TypeResolver<decltype(T::name)>::Get()},
//
//#define REFLECT_STRUCT_END() \
//		}; \
//	}

