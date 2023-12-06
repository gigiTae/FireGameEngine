#include "TypeDescriptor_Primitive.h"

#include "TypeDescriptor.h"
#include "TypeMap.h"
#include "TypeCheck.h"

/// <summary>
/// poiter 
/// </summary>
//template <typename T>
//Fire::Reflect::TypeDescriptor* Fire::Reflect::GetPrimitiveDescriptor<T*>()
//{
//	static TypeDescriptor_Pointer<T> typeDesc;
//	TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
//	return &typeDesc;
//}


/// <summary>
/// int
/// </summary>
template <>
Fire::Reflect::TypeDescriptor* Fire::Reflect::GetPrimitiveDescriptor<int>()
{
	static TypeDescriptor_Int typeDesc;
	TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);

	return &typeDesc;
}


/// <summary>
/// float
/// </summary>
template <>
Fire::Reflect::TypeDescriptor* Fire::Reflect::GetPrimitiveDescriptor<float>()
{
	static TypeDescriptor_Float typeDesc;
	TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
	return &typeDesc;
}

/// <summary>
/// double
/// </summary>
template<>
Fire::Reflect::TypeDescriptor* Fire::Reflect::GetPrimitiveDescriptor<double>()
{
	static TypeDescriptor_Double typeDesc;
	TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
	return &typeDesc;
}

/// <summary>
/// bool
/// </summary>
template<>
Fire::Reflect::TypeDescriptor* Fire::Reflect::GetPrimitiveDescriptor<bool>()
{
	static TypeDescriptor_Bool typeDesc;
	TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
	return &typeDesc;
}