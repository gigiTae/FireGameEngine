#pragma once

#include "ExportDefine.h"
#include "WindowInfomation.h"
 
namespace ImpGraphics {	class IImpGraphicsEngine; }
namespace ImpEngineModule {	class EngineModule;}

namespace ImpGameEngine
{
	class CameraSystem;
	// <summary>
	// 게임엔진
	// 
	// </summary>
	class IMP_ENGNIE_API ImpGameEngine
	{
	public:
		ImpGameEngine();
		~ImpGameEngine();

		// GameEngine 초기화
		void Initialize(WindowInfomation info);
		
		// 게임엔진 루프	
		void Process();
		
		// GameEngine 종료
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