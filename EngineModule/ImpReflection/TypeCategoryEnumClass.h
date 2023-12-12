#pragma once

namespace ImpReflection
{
	enum class TypeCategory
	{
		Class, // Struct, Class 
		Primitive, // int, float, bool , std::vector µîµî
		EnumClass, // enum class , enum(x)
		None // error
	};

}