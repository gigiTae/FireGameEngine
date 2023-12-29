#pragma once

namespace ImpGraphics
{
	class IImpGraphicsEngine;
}

namespace ImpGameEngine
{

	/// <summary>
	/// ���Ӹ��� �׷��Ƚ������� ������ ���ο��� ������ �����ϴ� ����
	/// 
	/// </summary>
	class RenderingSystem
		:ImpEngineModule::EventSubscriber<ImpEngineModule::Event::OnEntityCreated>
		, ImpEngineModule::EventSubscriber<ImpEngineModule::Event::OnEntityDestroyed>
		, ImpEngineModule::EventSubscriber<ImpEngineModule::Event::OnEntityStarted>
	{
	public:
		RenderingSystem();
		~RenderingSystem();

		// �ʱ�ȭ�� �׷��Ƚ������� ��������� �����´�.
		void Initialize(ImpGraphics::IImpGraphicsEngine* graphics, ImpEngineModule::EngineModule* module);

		// �������� �׷��Ƚ��� �����ؾ��ϴ� ������ �����Ѵ�.
		void Update();

		// ����
		void Finalize();

#pragma region Event
		// Entity ���������� �̺�Ʈ�� ó���Ѵ�.
		void Receive(ImpEngineModule::World* world, const ImpEngineModule::Event::OnEntityCreated& event);

		// Entity Start�� ���� �̺�Ʈ�� ó���Ѵ�.
		void Receive(ImpEngineModule::World* world, const ImpEngineModule::Event::OnEntityStarted& event);

		// Entity �Ҹ꿡���� �̺�Ʈ�� ó���Ѵ�.
		void Receive(ImpEngineModule::World* world, const ImpEngineModule::Event::OnEntityDestroyed& event);

#pragma endregion Event

	private:
		ImpGraphics::IImpGraphicsEngine* _graphicsEngine;
		ImpEngineModule::EngineModule* _engineModule;

	};


}