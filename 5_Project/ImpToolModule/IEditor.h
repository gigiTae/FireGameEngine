#pragma once

#include <d3d11.h>

namespace IImpGraphicsEngine { class IImpGraphicsEngine; }

namespace ImpToolModule
{

	/// <summary>
	/// Editor Interface
	/// ImGui , dx11 ���
	/// </summary>
	class IEditor
	{
	public:
		virtual ~IEditor(){}

		/// <summary>
		/// Editor �ʱ�ȭ, dx11,winAPI,imgui�� ����Ѵ�.
		/// </summary>
		virtual void Initialize(HWND hWnd, void* device, void* deviceContext,
			ImpEngineModule::EngineModule* engineModule, ImpGraphics::IImpGraphicsEngine* grahicsEngnie) abstract;

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		virtual void Finalize() abstract;

		/// <summary>
		/// GUI������ Editor�� �����Ѵ�.
		/// </summary>
		virtual void Update()abstract;

		/// <summary>
		/// ���ο� �������� ������ imgui���� �����Ѵ�.
		/// </summary>
		virtual void NewFrame() abstract;

		/// <summary>
		/// GUI�� �׸���.
		/// </summary>
		virtual void EndRender() abstract;

		/// Tool�� ī�޶� ��ȯ�Ѵ�.
		virtual ImpEngineModule::Entity* GetToolCamera()const abstract;
	};


}