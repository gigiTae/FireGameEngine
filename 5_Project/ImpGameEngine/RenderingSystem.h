#pragma once

namespace ImpGraphics
{
	class IImpGraphicsEngine;
}

namespace ImpGameEngine
{

	/// <summary>
	/// 게임모듈과 그래픽스엔진의 정보를 서로에게 정보를 전달하는 역할
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

		// 초기화된 그래픽스엔진과 엔진모듈을 가져온다.
		void Initialize(ImpGraphics::IImpGraphicsEngine* graphics, ImpEngineModule::EngineModule* module);

		// 매프레임 그래픽스에 전달해야하는 정보를 전달한다.
		void Update();

		// 종료
		void Finalize();

#pragma region Event
		// Entity 생성에대한 이벤트를 처리한다.
		void Receive(ImpEngineModule::World* world, const ImpEngineModule::Event::OnEntityCreated& event);

		// Entity Start에 대한 이벤트를 처리한다.
		void Receive(ImpEngineModule::World* world, const ImpEngineModule::Event::OnEntityStarted& event);

		// Entity 소멸에대한 이벤트를 처리한다.
		void Receive(ImpEngineModule::World* world, const ImpEngineModule::Event::OnEntityDestroyed& event);

#pragma endregion Event

	private:
		ImpGraphics::IImpGraphicsEngine* _graphicsEngine;
		ImpEngineModule::EngineModule* _engineModule;

	};


}