#pragma once

#include <d3d11.h> // dx11 ������

namespace ToolModule
{
class ImGuiManager
{
public:
	ImGuiManager();
	~ImGuiManager();

	// �ʱ�ȭ 
	void Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	// ����
	void Finalize();
	void NewFrame();
	void EndRnder();
};
}