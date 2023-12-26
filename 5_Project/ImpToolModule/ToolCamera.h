#pragma once

namespace ImpToolModule
{
	/// <summary>
	/// Tool 전용 카메라
	/// </summary>
	class ToolCamera
	{
	public:
		ToolCamera();
		~ToolCamera();

		// 초기화
		void Initialize(ImpEngineModule::EngineModule* engineModule);
		// 카메라 이동 처리
		void Update();
		// 종료
		void Finalize();

		ImpEngineModule::Entity* GetEntity()const { return _ent.get(); }

	private:
		std::unique_ptr<ImpEngineModule::Entity> _ent;
		ImpEngineModule::EngineModule* _engineModule;
	};


}