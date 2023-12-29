#pragma once

#include "Event.h"
#include "EventSubscriber.h"

namespace ImpEngineModule
{
	/// <summary>
	/// 충돌을 처리하는 매니져
	/// </summary>
	class CollisionManager
		:public EventSubscriber<Event::OnEntityDestroyed>,
		public EventSubscriber<Event::OnEntityStarted>
	{
	public:
		CollisionManager();
		~CollisionManager();

		// 이번프레임의 충돌을 체크한다.
		void Update();


	private:

		
	};


}