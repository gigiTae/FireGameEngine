#pragma once

#include "Event.h"
#include "EventSubscriber.h"

namespace ImpEngineModule
{
	/// <summary>
	/// �浹�� ó���ϴ� �Ŵ���
	/// </summary>
	class CollisionManager
		:public EventSubscriber<Event::OnEntityDestroyed>,
		public EventSubscriber<Event::OnEntityStarted>
	{
	public:
		CollisionManager();
		~CollisionManager();

		// �̹��������� �浹�� üũ�Ѵ�.
		void Update();


	private:

		
	};


}