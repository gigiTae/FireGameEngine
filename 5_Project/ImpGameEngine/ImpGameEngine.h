#pragma once

#include "IImpEngine.h"

namespace ImpGraphics { class IImpGraphicsEngine; }
namespace ImpEngineModule { class EngineModule; }

namespace ImpGameEngine
{
	class CameraSystem;
	class RenderingSystem;

	// <summary>
	// ���ӿ���
	// 
	// </summary>
	class ImpGameEngine : public IImpEngine
	{
	public:
		ImpGameEngine();
		~ImpGameEngine();

		// GameEngine �ʱ�ȭ
		void Initialize(WindowInfomation info) override;

		// ���ӿ��� ����	
		void Process() override;

		// GameEngine ����
		void Finalize() override;

	private:
		ImpGraphics::IImpGraphicsEngine* _graphicsEngine;
		ImpEngineModule::EngineModule* _engineModule;

		CameraSystem* _cameraSystem;
		RenderingSystem* _renderingSystem;
	};


}