#pragma once

#include "EventSubscriber.h"

namespace ImpEngineModule
{
	class World;

	/// <summary>
	/// World���� �߻��ϴ� �پ��� �̺�Ʈ���� ó���Ѵ�.
	/// ���߻���� �̿��� �̺�Ʈ �ý���
	/// </summary>
	class EventManager
	{
	public:
		EventManager();
		~EventManager();
	    
		void Initialize(World* world);

		void Finalize();

		void Update();
		
		// �ش��ϴ� �������� �����ڵ��� ��� �����Ѵ�.
		void UnSubScribeAll(void* subscriber);

		// �̺�Ʈ �����ڵ鿡�� �̺�Ʈ �ݹ��Լ��� ȣ���Ѵ�.
		template<typename T>
		void Emit(const T& event);

		// �ش��ϴ� �̺�Ʈ�� �ݹ��� ���� �� �ֵ��� �����Ѵ�.
		template<typename T>
		void SubScribe(EventSubscriber<T>* subscriber);

		// �ش��ϴ� �̺�Ʈ�� �ݹ��� �� �̻� ���� �ʴ´�.
		template <typename T>
		void UnSubScribe(EventSubscriber<T>* subscriber);

	private:
		std::unordered_map<TypeIndex, std::vector<ISubscriber*>> _subscribers;
		World* _world;

	};

	template<typename T>
	void ImpEngineModule::EventManager::Emit(const T& event)
	{
		auto iter = _subscribers.find(GetTypeIndex<T>());

		if (iter != _subscribers.end())
		{
			for (ISubscriber* iSubScriber : iter->second)
			{
				EventSubscriber<T>* subscriber = reinterpret_cast<EventSubscriber<T>*>(iSubScriber);

				subscriber->Receive(_world, event);
			}
		}
	}

	template <typename T>
	void ImpEngineModule::EventManager::UnSubScribe(EventSubscriber<T>* subscriber)
	{
		TypeIndex index = GetTypeIndex<T>();
		auto iter = _subscribers.find(index);
		
		if (iter != _subscribers.end())
		{
			auto& vec = iter->second;

			vec.erase(std::find(vec.begin, vec.end(), subscriber), vec.end());

			if (vec.size() == 0)
			{
				_subscribers.erase(iter);
			}
		}
	}

	template<typename T>
	void ImpEngineModule::EventManager::SubScribe(EventSubscriber<T>* subscriber)
	{
		TypeIndex index = GetTypeIndex<T>();
		auto iter = _subscribers.find(index);

		if (iter != _subscribers.end())
		{
			std::vector<ISubscriber*> vec;
			vec.push_back(subscriber);
			_subscribers.insert({ index,vec });
		}
		else
		{
			iter->second.push_back(subscriber);
		}
	}

}