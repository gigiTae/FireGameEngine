#pragma once

#include "../EntityComponentSystem/ReflectionHeader.h"

namespace Fire
{
	namespace Component
	{

		struct Camera
		{
			bool isMain = true;
			float cameraSpeed = 10.f;
		};
	}
}


