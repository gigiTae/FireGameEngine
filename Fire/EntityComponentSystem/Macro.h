#pragma once


// My Reflection

#pragma region StructMacro

#define DECLARE_FREIND_WITH_REFECTION(type)\
		friend class Fire::Reflect::ReflectCheck<type>;

#define REFLECT_CHECK(type)\
		template<>\
		struct Fire::Reflect::ReflectCheck<type>\
		{\
		public:\
			constexpr static bool IsReflect = true;\
			static struct Fire::Reflect::TypeDescriptor_Struct Reflection;\
			static void InitReflection(Fire::Reflect::TypeDescriptor_Struct*);\
		};

#define BEGIN_REFLECTION(type)\
		Fire::Reflect::TypeDescriptor_Struct Fire::Reflect::ReflectCheck<type>::Reflection\
						{Fire::Reflect::ReflectCheck<type>::InitReflection};\
		void Fire::Reflect::ReflectCheck<type>::InitReflection(Fire::Reflect::TypeDescriptor_Struct* desc)\
			{\
				using T = type; \
				Fire::Reflect::TypeMap::GetTypeMap()->AddType(#type,desc);\
				Fire::Reflect::TypeMap::GetTypeMap()->AddTypeIndex<T>(#type);\
				desc->category = TYPE_CATEGORY::STRUCT;\
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
		Fire::Reflect::TypeDescriptor_EnumClass<type> Fire::Reflect::ReflectCheck<type>::Reflection\
{ Fire::Reflect::ReflectCheck<type>::InitReflection };\
void Fire::Reflect::ReflectCheck<type>::InitReflection(Fire::Reflect::TypeDescriptor_EnumClass<type>* desc)\
{\
	using T = type;\
	desc->name = #type;\
	desc->category = TYPE_CATEGORY::ENUMCLASS;\
	desc->size = sizeof(T);\
	Fire::Reflect::TypeMap::GetTypeMap()->AddType(#type, desc);\
	Fire::Reflect::TypeMap::GetTypeMap()->AddTypeIndex<T>(#type);

#define ENUM_MEMBER_REFLECTION(name)\
	desc->AddEnumMember(#name, { T::name, static_cast<int>(T::name)});

#define END_REFLECTION_ENUM()\
		};\

#pragma endregion
