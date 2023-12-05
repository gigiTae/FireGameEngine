#pragma once

#include <d3d11.h> // dx11 종속적

#include "IToolModule.h"
#include "ComponentEditor.h"
#include "EntityEditor.h"
#include "SystemEditor.h"

namespace ToolModule
{
	class FireEditor : public IToolModule
	{
	public:
		FireEditor();
		~FireEditor();

		// 초기화 
		void Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
		// 해제
		void Finalize() override;
		void NewFrame() override;
		void EndRender() override;

		void Load(class Fire::ECS::World* world) override;

	private:
		void StartEntityEditor(class Fire::ECS::World* world);
		void StartComponentEditor(class Fire::ECS::World* world);
		void StartSystemEditor(class Fire::ECS::World* world);

	private:
		EntityEditor entityEditor;
		ComponentEditor compentEditor;
		SystemEditor systemEditor;

	};
}