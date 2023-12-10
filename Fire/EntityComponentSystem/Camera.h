#pragma once

#include "../EntityComponentSystem/ReflectionHeader.h"

namespace Fire
{
	namespace Component
	{

		struct Camera
		{
			bool isMain = true;
		
		};
	}
}

#ifndef CAMERA_H
#define CAMERA_H

#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::Camera)
BEGIN_REFLECTION(Fire::Component::Camera)
MEMBER_REFLECTION(isMain)
END_REFLECTION()

#endif // !CAMERA_H

#endif