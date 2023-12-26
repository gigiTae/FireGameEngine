#pragma once

#include "../ImpGraphicsEngine/ImpGraphicsEngine.h"

namespace ImpGameEngine
{
	/// <summary>
	/// ī�޶� �����ϴ� �ý���
	/// </summary>
	class CameraSystem 
	{
	public:
		CameraSystem();
		~CameraSystem();

		/// �ʱ�ȭ
		void Initialize(ImpGraphics::IImpGraphicsEngine* graphicsEngine, ImpEngineModule::EngineModule* engineModule);
		
		// Tool ī�޶� ����
		void SetToolCamera(ImpEngineModule::Entity* main);

		// ī�޶� ������ �����Ѵ�.
		const ImpGraphics::CameraInfo& GetCameraInfo();

	private:
		// �׷��Ƚ� ������ �Ѱ��� ī�޶� ������ �����Ѵ�.
		void SetCameraInfo(ImpEngineModule::Entity* main);

	private:
		ImpEngineModule::Entity* _toolCamera;
		ImpEngineModule::EngineModule* _engineModule;
		ImpGraphics::CameraInfo _cameraInfo;
		ImpGraphics::IImpGraphicsEngine* _graphicsEngine;
	};

}

