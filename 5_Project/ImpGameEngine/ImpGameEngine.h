#pragma once

#include "ExportDefine.h"
#include "WindowInfomation.h"
 
namespace ImpGraphics {	class IImpGraphicsEngine; }
namespace ImpEngineModule {	class EngineModule;}

namespace ImpGameEngine
{
	class CameraSystem;
	// <summary>
	// ���ӿ���
	// 
	// </summary>
	class IMP_ENGNIE_API ImpGameEngine
	{
	public:
		ImpGameEngine();
		~ImpGameEngine();

		// GameEngine �ʱ�ȭ
		void Initialize(WindowInfomation info);
		
		// ���ӿ��� ����	
		void Process();
		
		// GameEngine ����
		void Finalize();

	private:
		ImpGraphics::IImpGraphicsEngine* _graphicsEngine;
		ImpEngineModule::EngineModule* _engineModule;

		CameraSystem* _cameraSystem;

#ifdef IMP_EDITOR_MODE
		ImpToolModule::IEditor*_editor;
#endif 
	};


}