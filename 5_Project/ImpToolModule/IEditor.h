#pragma once

#include <d3d11.h>

namespace IImpGraphicsEngine { class IImpGraphicsEngine; }

namespace ImpToolModule
{

	/// <summary>
	/// Editor Interface
	/// ImGui , dx11 사용
	/// </summary>
	class IEditor
	{
	public:
		virtual ~IEditor(){}

		/// <summary>
		/// Editor 초기화, dx11,winAPI,imgui를 사용한다.
		/// </summary>
		virtual void Initialize(HWND hWnd, void* device, void* deviceContext,
			ImpEngineModule::EngineModule* engineModule, ImpGraphics::IImpGraphicsEngine* grahicsEngnie) abstract;

		/// <summary>
		/// 종료 함수
		/// </summary>
		virtual void Finalize() abstract;

		/// <summary>
		/// GUI정보를 Editor에 전달한다.
		/// </summary>
		virtual void Update()abstract;

		/// <summary>
		/// 새로운 프레임의 갱신을 imgui에게 전달한다.
		/// </summary>
		virtual void NewFrame() abstract;

		/// <summary>
		/// GUI를 그린다.
		/// </summary>
		virtual void EndRender() abstract;

		/// Tool용 카메라를 반환한다.
		virtual ImpEngineModule::Entity* GetToolCamera()const abstract;
	};


}