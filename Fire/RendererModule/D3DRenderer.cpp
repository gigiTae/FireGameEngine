#include "RendererPCH.h"
#include "D3DRenderer.h"
#include "Box.h"
#include "Cylinder.h"
#include "Grid.h"
#include "Sphere.h"
#include "GeoSphere.h"
#include "BaseAxis.h"
#include "InputLayout.h"
#include "ResourceManager.h"
#include "TextManager.h"
#include "Crate.h"
#include "BasicEffect.h"
#include "Camera.h"
#include "RenderingPipeline.h"

RendererModule::D3DRenderer::D3DRenderer()
	:m_d3dDevice(nullptr)
	, m_hWnd(nullptr)
	, m_d3dDeviceContext(nullptr)
	, m_featureLevel()
	, m_swapChain()
	, m_enable4xMass(false)
	, m_d3dRenderTargetView()
	, m_depthStencilView()
	, m_depthStencilBuffer()
	, m_screenWidth(0)
	, m_screenHeight(0)
	, m_resourceManager(nullptr)
	, m_box(nullptr)
	, m_grid(nullptr)
	, m_sphere(nullptr)
	, m_cylinder(nullptr)
	, m_geoSphere(nullptr)
	, m_baseAxis(nullptr)
	,m_camera(nullptr)
{
	m_resourceManager = std::make_unique<ResourceManager>();
	m_textManager = std::make_unique<TextManager>();
	m_camera = std::make_unique<Camera>();
	m_camera->LookAt(XMFLOAT3(8.0f, 8.0f, -8.0f), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 1.0f, 0));
}

RendererModule::D3DRenderer::~D3DRenderer()
{

}



void RendererModule::D3DRenderer::Initialize(HWND hWnd, int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_hWnd = hWnd;

	// ī�޶� ����
	XMVECTOR cameraPosition = XMVectorSet(0.f, 10.f, 10.f, 1.f);
	m_camera->SetLens(0.25f * MathModule::PI, static_cast<float>(m_screenWidth) / m_screenHeight, 1.0f, 1000.0f);

	InitializeD3D();

	InitializeResource();

	/// �Ŵ��� �ʱ�ȭ
	m_resourceManager->Initialize(m_d3dDevice.Get());
	m_textManager->Initialize(m_d3dDevice.Get(), m_rasterizerState[1].Get(), m_depthStencilState.Get());
	//pipeline->Initialize();

	/// �ӽ�
	InitializeObject();
}

void RendererModule::D3DRenderer::Finalize()
{
	delete m_grid;
	delete m_box;
	delete m_sphere;
	delete m_cylinder;
	delete m_geoSphere;
	delete m_baseAxis;
	delete m_crate;

	CoUninitialize();
}

void RendererModule::D3DRenderer::ClearScreen()
{
	float arr[4]{ 0.f,0.f,0.f,1.f };
	m_d3dDeviceContext->OMSetRenderTargets(1, m_d3dRenderTargetView.GetAddressOf(), nullptr);
	m_d3dDeviceContext->ClearRenderTargetView(m_d3dRenderTargetView.Get(), arr);

	// ���� ���۸� 1. Of��, ���ٽ� ���۸� 0���� �����.
	m_d3dDeviceContext->ClearDepthStencilView(m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void RendererModule::D3DRenderer::OnResize(int width, int height)
{
	m_screenWidth = width;
	m_screenHeight = height;

	m_d3dRenderTargetView.Reset();
	m_depthStencilView.Reset();
	m_depthStencilState.Reset();

	HR(m_swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));

	// 5. ��ȯ �罽�� �ĸ� ���ۿ� ���� ���� ��� �並 �����Ѵ�.
	ID3D11Texture2D* backBuffer = nullptr;
	HR(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	assert(backBuffer);

	HR(m_d3dDevice->CreateRenderTargetView(backBuffer, 0, m_d3dRenderTargetView.GetAddressOf()));

	backBuffer->Release();

	// 6. ����, ���ٽ� ���ۿ� �׿� ����Ǵ� ����,���ٽ� �並 �����Ѵ�.
	D3D11_TEXTURE2D_DESC depthStencilDesc{};
	depthStencilDesc.Width = m_screenWidth;
	depthStencilDesc.Height = m_screenHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// 4X MSAA�� ����ϴ°� ? �ݵ�� ��ȯ �罽 MSAA ������ ��ġ�ؾ���
	if (m_enable4xMass)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc, 0, m_depthStencilBuffer.GetAddressOf()));

	assert(m_depthStencilBuffer);
	HR(m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0, &m_depthStencilView));

	// 7. ���� ��� ��� ����,���ٽ� �並 Direct3D�� ����� �� �ֵ��� ������ ������������ ��� ���ձ� �ܰ迡 ���´�.
	m_d3dDeviceContext->OMSetRenderTargets(1, m_d3dRenderTargetView.GetAddressOf(), m_depthStencilView.Get());

	// 8. ����Ʈ�� �����Ѵ�. ����Ʈ 2�������ϸ� ȭ����� ���� 

	D3D11_VIEWPORT vp{};
	vp.TopLeftX = 0.f;
	vp.TopLeftY = 0.f;
	vp.Width = static_cast<float>(m_screenWidth);
	vp.Height = static_cast<float>(m_screenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_d3dDeviceContext->RSSetViewports(1, &vp);

	float aspectRatio = static_cast<float>(m_screenWidth) / m_screenHeight;
	
	m_camera->SetLens(0.25f * MathModule::PI, aspectRatio, 1.0f, 1000.0f);
}

void RendererModule::D3DRenderer::Render()
{
	m_camera->UpdateViewMatrix();

	// �׸��� �׷����� 
	XMMATRIX worldMatrix = XMMatrixIdentity();
	XMMATRIX viewMatrix = m_camera->View();
	XMMATRIX projectMatrix = m_camera->Proj();

	m_box->Update(worldMatrix, viewMatrix, projectMatrix);
	//m_box->Render();

	m_grid->Update(worldMatrix, viewMatrix, projectMatrix);
	//m_grid->Render();

	m_cylinder->Update(worldMatrix, viewMatrix, projectMatrix);
	//m_cylinder->Render();

	m_sphere->Update(worldMatrix, viewMatrix, projectMatrix);
	//m_sphere->Render();

	m_geoSphere->Update(worldMatrix, viewMatrix, projectMatrix);
	m_geoSphere->Render();

	m_baseAxis->Update(worldMatrix, viewMatrix, projectMatrix);
	m_baseAxis->Render();

	m_crate->Render();

	XMFLOAT3 cameraPos; 
	XMStoreFloat3(&cameraPos, m_camera->GetPositionXM());


	/// ī�޶� ��ġ 
	std::wstring cameraInfo = L"ī�޶� ��ġ X " 
		+ std::to_wstring(static_cast<int>(cameraPos.x)) + L" Y " 
		+ std::to_wstring(static_cast<int>(cameraPos.y)) + L" Z " 
		+ std::to_wstring(static_cast<int>(cameraPos.z));

	/// �ؽ�Ʈ ���
	m_textManager->DrawTextColor(XMFLOAT2(0.f, 10.f), XMFLOAT4(0.f, 1.f, 1.f, .1f), cameraInfo.c_str());

	m_d3dDeviceContext->OMGetDepthStencilState(m_depthStencilState.GetAddressOf(), 0);


}

void RendererModule::D3DRenderer::BeginRender()
{
	/// BeginRender
	ClearScreen();
}

void RendererModule::D3DRenderer::EndRender()
{
	/// EndRender 
	HR(m_swapChain->Present(1, 0));
	//swapChain->Present(1, 0); // Present with vsync
}

void RendererModule::D3DRenderer::InitializeD3D()
{
	/// ======================================================
	///                     Direct3D �ʱ�ȭ 
	/// ======================================================

	// Direct3D �ʱ�ȭ 8���� �ܰ�

	// 1. D3D11CreateDevice �Լ��� �̿��ؼ� ��ġ, �� ID3D11 Device �������̽���
	// ��ġ ����, �� ID3D11DeviceContext ���� ���̽��� �����Ѵ�. 

	UINT createDeviceFlags = 0;

#if defined (DEBUG) || defined (_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // ����� �뵵
#endif

	HRESULT hr = D3D11CreateDevice(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		createDeviceFlags,
		0, 0,
		D3D11_SDK_VERSION,
		m_d3dDevice.GetAddressOf(),
		&m_featureLevel,
		m_d3dDeviceContext.GetAddressOf()
	);

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
	}

	if (m_featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
	}

	// 2. ID3D11Device::CheckMultisampleQualityLevels �޼��带 �̿��ؼ� 
	// 4XMSAA ǰ�� ���� ���� ���θ� �����Ѵ�.

	HR(m_d3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality));

	assert(m_4xMsaaQuality > 0);

	// 3. ������ ��ȯ �罽�� Ư���� �����ϴ� DXGI_SWAP_CHAIN_DESC ����ü�� ä���.

	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.Width = m_screenWidth;
	sd.BufferDesc.Height = m_screenHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 4XMASS�� ����ϴ°�?
	if (m_enable4xMass)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = m_hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// 4. ��ġ�� �����ϴµ� ����ߴ� IDXGIFactory �������̽��� �����ؼ� IDXGISwapChain �ν��Ͻ��� �����Ѵ�.

	IDXGIDevice* dxgiDevice = nullptr;
	HR(m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = nullptr;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = nullptr;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &sd, m_swapChain.GetAddressOf()));

	// COM �������̽� ����
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	// 5. ��ȯ �罽�� �ĸ� ���ۿ� ���� ���� ��� �並 �����Ѵ�.
	ID3D11Texture2D* backBuffer = nullptr;
	HR(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	assert(backBuffer);

	HR(m_d3dDevice->CreateRenderTargetView(backBuffer, 0, m_d3dRenderTargetView.GetAddressOf()));

	backBuffer->Release();

	// 6. ����, ���ٽ� ���ۿ� �׿� ����Ǵ� ����,���ٽ� �並 �����Ѵ�.
	D3D11_TEXTURE2D_DESC depthStencilDesc{};
	depthStencilDesc.Width = m_screenWidth;
	depthStencilDesc.Height = m_screenHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// 4X MSAA�� ����ϴ°� ? �ݵ�� ��ȯ �罽 MSAA ������ ��ġ�ؾ���
	if (m_enable4xMass)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc, 0, m_depthStencilBuffer.GetAddressOf()));

	assert(m_depthStencilBuffer);
	HR(m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0, &m_depthStencilView));

	// 7. ���� ��� ��� ����,���ٽ� �並 Direct3D�� ����� �� �ֵ��� ������ ������������ ��� ���ձ� �ܰ迡 ���´�.
	m_d3dDeviceContext->OMSetRenderTargets(1, m_d3dRenderTargetView.GetAddressOf(), m_depthStencilView.Get());

	// 8. ����Ʈ�� �����Ѵ�. ����Ʈ 2�������ϸ� ȭ����� ���� 

	D3D11_VIEWPORT vp{};
	vp.TopLeftX = 0.f;
	vp.TopLeftY = 0.f;
	vp.Width = static_cast<float>(m_screenWidth);
	vp.Height = static_cast<float>(m_screenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_d3dDeviceContext->RSSetViewports(1, &vp);
}

void RendererModule::D3DRenderer::InitializeResource()
{

	m_inputLayout = std::make_unique<InputLayout>();

	m_inputLayout->Initailize(m_d3dDevice.Get());

	// �����Ͷ����� ����
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
	rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME; // ���̾� ������ ���
	//rasterizerDesc.FillMode = D3D11_FILL_SOLID; // �ﰢ�� ä��� ��� 
	//rasterizerDesc.CullMode = D3D11_CULL_BACK; // �ĸ� �ﰢ�� ����
	rasterizerDesc.CullMode = D3D11_CULL_BACK;  // ī�޶� ���� ��� ������ Ȱ��ȭ
	rasterizerDesc.FrontCounterClockwise = false; // �ð� �������� �׷����� �ﰢ��
	rasterizerDesc.DepthClipEnable = true; // ���� Ŭ���� Ȱ��ȭ

	m_d3dDevice->CreateRasterizerState(&rasterizerDesc, m_rasterizerState[0].GetAddressOf());

	rasterizerDesc.FillMode = D3D11_FILL_SOLID;

	m_d3dDevice->CreateRasterizerState(&rasterizerDesc, m_rasterizerState[1].GetAddressOf());

	m_d3dDeviceContext->RSSetState(m_rasterizerState[0].Get());


	// ��Ʈ�� DSS
	D3D11_DEPTH_STENCIL_DESC equalsDesc;
	ZeroMemory(&equalsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	equalsDesc.DepthEnable = true;
	equalsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;		// ���̹��ۿ� ����� �Ѵ�
	equalsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	HR(m_d3dDevice->CreateDepthStencilState(&equalsDesc, m_depthStencilState.GetAddressOf()));
}

void RendererModule::D3DRenderer::InitializeObject()
{
	m_box = new Box(m_d3dDevice.Get(), m_d3dDeviceContext.Get(), m_rasterizerState[0].Get());
	m_box->Initialize();

	m_grid = new Grid(m_d3dDevice.Get(), m_d3dDeviceContext.Get(), m_rasterizerState[0].Get());
	m_grid->Initialize(100, 100, 10, 10);

	m_cylinder = new Cylinder(m_d3dDevice.Get(), m_d3dDeviceContext.Get(), m_rasterizerState[0].Get());
	m_cylinder->Initailize(10.f, 0.f, 10.f, 100, 100);

	m_sphere = new Sphere(m_d3dDevice.Get(), m_d3dDeviceContext.Get(), m_rasterizerState[0].Get());
	m_sphere->Initialize(10.f, 20, 20);

	m_geoSphere = new GeoSphere(m_d3dDevice.Get(), m_d3dDeviceContext.Get(), m_rasterizerState[0].Get());
	m_geoSphere->Initilize(10.f, 2);
	
	m_baseAxis = new BaseAxis(m_d3dDevice.Get(), m_d3dDeviceContext.Get(), m_rasterizerState[1].Get());
	m_baseAxis->Initalize();

	BasicEffect* ef = dynamic_cast<BasicEffect*>(m_resourceManager->GetEffect(L"Basic"));

	m_crate = new Crate(m_d3dDevice.Get(), m_d3dDeviceContext.Get()
		, m_rasterizerState[0].Get(), m_inputLayout->GetBasicLayout(),ef);

	m_crate->Initialize(10, 10, 10);

}

