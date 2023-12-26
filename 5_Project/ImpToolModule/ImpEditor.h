#pragma once
#include "IEditor.h"

namespace ImpToolModule
{
	class WorldViewer;
	class EntityViewer;
	class ComponentViewer;
	class ResourceViewer;
	class ToolCamera;

	/// <summary>
	/// ���� ����� ��Ƽ�� �������Ѵ�. 
	/// �ٸ� �����͵��� �����Ѵ�.
	/// 
	/// </summary>
	class ImpEditor : public IEditor
	{
	public:
		ImpEditor();
		~ImpEditor();

	public:
		// Editor �ʱ�ȭ
		void Initialize(HWND hWnd, void* device, void* deviceContext, ImpEngineModule::EngineModule* engineModule)override;

		// Editor ����
		void Finalize()override;

		// Editor�� �����Ѵ�.
		void Update()override;

		// ImGui ���ο� ������ ����
		void NewFrame() override;

		// GUI�� �׸���.
		void EndRender() override;

		// Tool ī�޶� ���´�.
		ImpEngineModule::Entity* GetToolCamera()const override;

	private:
		void InitializeImGui(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		void FinalizeImGui();

	private:
		ImpEngineModule::EngineModule* _engineModule;

		std::unique_ptr<WorldViewer> _worldViewer;
		std::unique_ptr<EntityViewer> _entityViewer;
		std::unique_ptr<ComponentViewer> _componentViewer;
		std::unique_ptr<ResourceViewer> _resourceViewer;

		// ī�޶� ����
		std::unique_ptr<ToolCamera> _toolCamera;
	};

}