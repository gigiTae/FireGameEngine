#pragma once
#include "ReflectionHeader.h"

enum class OBJECT_TYPE
{
	CAMERA,
	MESH,
	LIGHT,
	NONE,
};

REFLECT_CHECK_ENUM(OBJECT_TYPE)
