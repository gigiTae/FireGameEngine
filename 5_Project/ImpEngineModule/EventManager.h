#pragma once

namespace ImpEngineModule
{
	struct Event
	{
		std::function<void()> function;
		EventType type;
	};

	/// <summary>
	/// World���� �߻��ϴ� �پ��� �̺�Ʈ���� ó���Ѵ�.
	/// </summary>
	class EventManager
	{
	public:
		EventManager();
		~EventManager();
	    
		/// �ʱ�ȭ 
		void Initialize();

		/// ����
		void Finalize();

		/// �̺�Ʈť�� �̺�Ʈ���� ó���Ѵ�.
		void Update();

		/// �̺�Ʈ ť�� �̺�Ʈ�� �ִ´�.
		void PushBackEvent(const Event& event);
	private:
		std::vector<Event> _eventQueue;

	};


}