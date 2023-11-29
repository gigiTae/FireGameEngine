#pragma once
#include "ISubscriber.h"

namespace Fire
{
	namespace ECS
	{
		class World;

		template <typename T>
		class EventSubscriber :	public ISubscriber
		{
		public:
			virtual ~EventSubscriber() {}

			virtual void Receive(World* wolrd, const T& event) = 0;
		};
	}
}
