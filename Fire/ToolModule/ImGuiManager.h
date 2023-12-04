#pragma once

#include <d3d11.h> // dx11 종속적
#include "IToolModule.h"

namespace ToolModule
{
class ImGuiManager : public IToolModule
{
public:
	ImGuiManager();
	~ImGuiManager();

	// 초기화 
	void Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
	// 해제
	void Finalize() override;
	void NewFrame() override;
	void EndRender() override;
};
}