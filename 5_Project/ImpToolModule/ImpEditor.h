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
	/// 가장 상단의 에티터 역할을한다. 
	/// 다른 에디터들을 포함한다.
	/// 
	/// </summary>
	class ImpEditor : public IEditor
	{
	public:
		ImpEditor();
		~ImpEditor();

	public:
		// Editor 초기화
		void Initialize(HWND hWnd, void* device, void* deviceContext, ImpEngineModule::EngineModule* engineModule)override;

		// Editor 종료
		void Finalize()override;

		// Editor를 갱신한다.
		void Update()override;

		// ImGui 새로운 프레임 갱신
		void NewFrame() override;

		// GUI를 그린다.
		void EndRender() override;

		// Tool 카메라를 얻어온다.
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

		// 카메라 관련
		std::unique_ptr<ToolCamera> _toolCamera;
	};

}