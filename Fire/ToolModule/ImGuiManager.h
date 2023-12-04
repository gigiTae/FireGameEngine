#pragma once

#include <d3d11.h> // dx11 ������
#include "IToolModule.h"

namespace ToolModule
{
class ImGuiManager : public IToolModule
{
public:
	ImGuiManager();
	~ImGuiManager();

	// �ʱ�ȭ 
	void Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
	// ����
	void Finalize() override;
	void NewFrame() override;
	void EndRender() override;
};
}