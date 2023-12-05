#pragma once

#include <string>
#include "../Reflection/ReflectionHeader.h"
#include "Transform.h"
namespace Fire
{
	namespace Component
	{
		struct Name
		{
			std::string name;
			Fire::Component::Transform pos;
		};
	}
}

BEGIN_REFLECTION(Fire::Component::Name)
MEMBER_REFLECTION(name)
MEMBER_REFLECTION(pos)
END_REFLECTION()

//template<>
//class Fire::Reflect::ReflectCheck<Fire::Component::Name>
//{
//public:
//	constexpr static bool IsReflect = true; 
//	static struct Fire::Reflect::TypeDescriptor_Struct Reflection; 
//	static void InitReflection(Fire::Reflect::TypeDescriptor_Struct*); 
//};
//Fire::Reflect::TypeDescriptor_Struct Fire::Reflect::ReflectCheck<Fire::Component::Name>::Reflection
//{Fire::Reflect::ReflectCheck<Fire::Component::Name>::InitReflection};
//void Fire::Reflect::ReflectCheck<Fire::Component::Name>::InitReflection(Fire::Reflect::TypeDescriptor_Struct* desc)
//{
//using T = Fire::Component::Name;
//Fire::Reflect::TypeMap::GetTypeMap()->AddType("Fire::Component::Name", desc);
//Fire::Reflect::TypeMap::GetTypeMap()->AddTypeIndex<T>("Fire::Component::Name"); 
//desc->name = "Fire::Component::Name";
//desc->size = sizeof(T); \
//desc->members = {
//{#name, offsetof(T,name), Fire::Reflect::TypeResolver<decltype(T::name)>::Get()},
//	}; \
//}
