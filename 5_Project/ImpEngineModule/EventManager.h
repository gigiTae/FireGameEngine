#pragma once

namespace ImpEngineModule
{
	struct Event
	{
		std::function<void()> function;
		EventType type;
	};

	/// <summary>
	/// World에서 발생하는 다양한 이벤트들을 처리한다.
	/// </summary>
	class EventManager
	{
	public:
		EventManager();
		~EventManager();
	    
		/// 초기화 
		void Initialize();

		/// 종료
		void Finalize();

		/// 이벤트큐의 이벤트들을 처리한다.
		void Update();

		/// 이벤트 큐에 이벤트를 넣는다.
		void PushBackEvent(const Event& event);
	private:
		std::vector<Event> _eventQueue;

	};


}