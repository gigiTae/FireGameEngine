#pragma once

namespace ImpToolModule
{
	/// <summary>
	/// Tool ���� ī�޶�
	/// </summary>
	class ToolCamera
	{
	public:
		ToolCamera();
		~ToolCamera();

		// �ʱ�ȭ
		void Initialize(ImpEngineModule::EngineModule* engineModule);
		// ī�޶� �̵� ó��
		void Update();
		// ����
		void Finalize();

		ImpEngineModule::Entity* GetEntity()const { return _ent.get(); }

	private:
		std::unique_ptr<ImpEngineModule::Entity> _ent;
		ImpEngineModule::EngineModule* _engineModule;
	};


}