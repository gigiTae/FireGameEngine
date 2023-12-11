#pragma once



struct SimpleMesh;
class Box;
class Grid;
class Cylinder;
class Sphere;
class GeoSphere;
class BaseAxis;

namespace RendererModule
{
class Crate;
class InputLayout;
class ResourceManager;
class TextManager;
class Camera;
class RenderingPipeline;
}

namespace RendererModule
{
	/// <summary>
	///  DX11  
	/// 
	/// 
	/// 2023.9.8 23:22 gitae
	/// </summary>
class  D3DRenderer
{
public:
	D3DRenderer();
	~D3DRenderer();

	void Initialize(HWND hWnd, int screenWidth, int screenHeight);
	void Finalize();
	void ClearScreen();
	void OnResize(int width, int height);
	void Render();
	void BeginRender();
	void EndRender();

	TextManager* GetTextManager() const { return m_textManager.get(); }
	ID3D11Device* GetDevice() const { return m_d3dDevice.Get(); }
	ID3D11DeviceContext* GetDeviceContext() const { return m_d3dDeviceContext.Get(); }
	Camera* GetCamera() { return m_camera.get(); }

private:
	void InitializeD3D();
	void InitializeResource();
	void InitializeObject();

private:
	int m_screenWidth;
	int m_screenHeight;

	HWND m_hWnd; // ���� ������ �ڵ� 
	bool m_enable4xMass; // 4XMSAA�� ����Ѵٸ� true�� ����
	UINT m_4xMsaaQuality;

	std::unique_ptr<RenderingPipeline> pipeline;
	std::unique_ptr<ResourceManager> m_resourceManager;
	std::unique_ptr<TextManager> m_textManager;

	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<InputLayout> m_inputLayout; // �Է¼��� ��ġ

	D3D_FEATURE_LEVEL m_featureLevel;
	ComPtr<IDXGISwapChain> m_swapChain;
	ComPtr<ID3D11Device> m_d3dDevice;
	ComPtr<ID3D11DeviceContext> m_d3dDeviceContext;
	ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	ComPtr<ID3D11RenderTargetView> m_d3dRenderTargetView;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;

#pragma region RenderState
	ComPtr<ID3D11RasterizerState> m_rasterizerState[2];
	ComPtr<ID3D11DepthStencilState> m_depthStencilState;

#pragma endregion

		/// ===================== �ӽð�ü ================================
	Box* m_box;
	Grid* m_grid;
	Cylinder* m_cylinder;
	Sphere* m_sphere;
	GeoSphere* m_geoSphere;
	BaseAxis* m_baseAxis;
	Crate* m_crate;
};
}
