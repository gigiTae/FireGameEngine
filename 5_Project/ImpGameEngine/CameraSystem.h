#pragma once

#include "../ImpGraphicsEngine/ImpGraphicsEngine.h"

namespace ImpGameEngine
{
	/// <summary>
	/// 카메라를 관리하는 시스템
	/// </summary>
	class CameraSystem 
	{
	public:
		CameraSystem();
		~CameraSystem();

		/// 초기화
		void Initialize(ImpGraphics::IImpGraphicsEngine* graphicsEngine, ImpEngineModule::EngineModule* engineModule);
		
		// Tool 카메라를 설정
		void SetToolCamera(ImpEngineModule::Entity* main);

		// 카메라 정보를 설정한다.
		const ImpGraphics::CameraInfo& GetCameraInfo();

	private:
		// 그래픽스 엔진에 넘겨줄 카메라 정보를 설정한다.
		void SetCameraInfo(ImpEngineModule::Entity* main);

	private:
		ImpEngineModule::Entity* _toolCamera;
		ImpEngineModule::EngineModule* _engineModule;
		ImpGraphics::CameraInfo _cameraInfo;
		ImpGraphics::IImpGraphicsEngine* _graphicsEngine;
	};

}

