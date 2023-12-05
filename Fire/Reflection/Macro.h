#pragma once


// My Reflection

#pragma region StructMacro

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
				using T = type; \
				Fire::Reflect::TypeMap::GetTypeMap()->AddType(#type,desc);\
				Fire::Reflect::TypeMap::GetTypeMap()->AddTypeIndex<T>(#type);\
				desc->name = #type; \
				desc->size = sizeof(T); \
				desc->members = {

#define MEMBER_REFLECTION(name)\
			{#name, offsetof(T,name), Fire::Reflect::TypeResolver<decltype(T::name)>::Get()},

#define END_REFLECTION()\
			}; \
		}

#pragma endregion

#pragma region EnumClassMacro

#define REFLECT_CHECK_ENUM(type)\
template<>\
class Fire::Reflect::ReflectCheck<type>\
{\
public:\
	constexpr static bool IsReflect = true;\
	static struct Fire::Reflect::TypeDescriptor_EnumClass<type> Reflection;\
	static void InitReflection(Fire::Reflect::TypeDescriptor_EnumClass<type>*);\
};

#define BEGIN_REFLECTION_ENUM(type)\
		REFLECT_CHECK_ENUM(type)\
		Fire::Reflect::TypeDescriptor_EnumClass<COLOR> Fire::Reflect::ReflectCheck<COLOR>::Reflection\
{ Fire::Reflect::ReflectCheck<COLOR>::InitReflection };\
void Fire::Reflect::ReflectCheck<COLOR>::InitReflection(Fire::Reflect::TypeDescriptor_EnumClass<COLOR>* desc)\
{\
	using T = COLOR;\
	desc->name = "COLOR";\
	desc->size = sizeof(T);\
	Fire::Reflect::TypeMap::GetTypeMap()->AddType(#type, desc);\
	Fire::Reflect::TypeMap::GetTypeMap()->AddTypeIndex<T>(#type);

#define ENUM_MEMBER_REFLECTION(name)\
	desc->AddEnumMember(#name, { T::name, static_cast<int>(T::name)});

#define END_REFLECTION_ENUM()\
		};\

#pragma endregion
