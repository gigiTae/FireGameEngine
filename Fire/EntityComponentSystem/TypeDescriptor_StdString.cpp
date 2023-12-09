#include "TypeDescriptor_StdString.h"
#include "TypeCheck.h"
#include "TypeDescriptor.h"

/// <summary>
/// string
/// </summary>
template <>
Fire::Reflect::TypeDescriptor* Fire::Reflect::GetPrimitiveDescriptor<std::string>()
{
	static TypeDescriptor_StdString typeDesc;
	TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
	return &typeDesc;
}


/// <summary>
/// wstring
/// </summary>
template <>
Fire::Reflect::TypeDescriptor* Fire::Reflect::GetPrimitiveDescriptor<std::wstring>()
{
	static TypeDescriptor_StdWstring typeDesc;
	TypeMap::GetTypeMap()->AddType(typeDesc.GetFullName(), &typeDesc);
	return &typeDesc;
}
