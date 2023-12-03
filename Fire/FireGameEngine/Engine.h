#pragma once

#include "ExportDefine.h"

namespace Fire
{
	namespace EngineModule
	{
		class FIRE_ENGNIE_API Engine
		{

		public:
			Engine();
			~Engine();

		public:
			void Initialize();
			void Process();
			void Uninitialize();
		};
	}
}

