#include "pch.h"
#include "ImpRenderTarget.h"
#include "ImpDevice.h"

#include "Define.h"

using namespace ImpGraphics;

ImpRenderTarget::ImpRenderTarget(ImpDevice* device)
	:_device(device),
	_renderTargetView(nullptr),
	_depthStencilView(nullptr)

{
	
}

ImpRenderTarget::~ImpRenderTarget()
{
	ReleaseCOM(_depthStencilView);
	ReleaseCOM(_renderTargetView);
}

void ImpRenderTarget::Initialize(int width, int height)
{
	ID3D11Device* device = _device->GetDevice();
	ID3D11DeviceContext* deviceContext = _device->GetDeviceContext();
	IDXGISwapChain* swapChain = _device->GetSwapChain();

	assert(deviceContext);
	assert(device);
	assert(swapChain);

	ID3D11Texture2D* backBuffer = nullptr;
	HR(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	if (backBuffer == nullptr)
	{
		MessageBox(NULL, L"backBuffer가 nullptr입니다.", L"에러", MB_ICONERROR);
	}
	else
	{
		HR(device->CreateRenderTargetView(backBuffer, 0, &_renderTargetView));
	}
	ReleaseCOM(backBuffer);

	// Create the depth/stencil buffer and view.

	D3D11_TEXTURE2D_DESC depthStencilDesc{};

	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

// 	bool _enable4xMsaa;
// 	UINT _4xMsaaQuality;
// 	// Use 4X MSAA? --must match swap chain MSAA values.
// 	if (_enable4xMsaa)
// 	{
// 		depthStencilDesc.SampleDesc.Count = 4;
// 		depthStencilDesc.SampleDesc.Quality = _4xMsaaQuality - 1;
// 	}
// 	// No MSAA
// 	else
	
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	ID3D11Texture2D* depthStencilBuffer;
	HR(device->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer));
	if (depthStencilBuffer == nullptr)
	{
		MessageBox(NULL, L"depthStencilBuffer가 nullptr입니다.", L"에러", MB_ICONERROR);
	}
	else
	{
		HR(device->CreateDepthStencilView(depthStencilBuffer, 0, &_depthStencilView));
	}
	ReleaseCOM(depthStencilBuffer);

	/// 렌더타겟뷰, 뎁스/스탠실뷰를 파이프라인에 바인딩한다.
	deviceContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

	D3D11_VIEWPORT screenViewport{};

	/// 뷰포트 변환을 셋팅한다.
	screenViewport.TopLeftX = 0;
	screenViewport.TopLeftY = 0;
	screenViewport.Width = static_cast<float>(width);
	screenViewport.Height = static_cast<float>(height);
	screenViewport.MinDepth = 0.0f;
	screenViewport.MaxDepth = 1.0f;

	deviceContext->RSSetViewports(1, &screenViewport);
}

void ImpRenderTarget::OnResize(int width, int height)
{
	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	ReleaseCOM(_depthStencilView);
	ReleaseCOM(_renderTargetView);

	// Resize the swap chain and recreate the render target view.
	IDXGISwapChain* swapChain = _device->GetSwapChain();
	HR(swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	Initialize(width, height);
}

void ImpRenderTarget::Clear()
{
	ID3D11DeviceContext* deviceContext = _device->GetDeviceContext();
	assert(deviceContext);

	// 랜더타겟 뷰를 클리어한다.
	const float backgroundColor[4] = { 0.8f, 0.2f, 0.2f, 1.0f };
	deviceContext->ClearRenderTargetView(_renderTargetView, backgroundColor);

	// 뎁스스탠실 뷰를 클리어한다.
	deviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	Bind();
}

void ImpRenderTarget::Bind()
{
	// 이전까지는 매 프레임 안 해도 됐지만
	// 추측으로는 IMGUI 에서 렌더 타겟이 여러 개가 되어서 바인딩을 해줘야 하는걸로 보인다.
	/// 렌더타겟뷰, 뎁스/스탠실뷰를 파이프라인에 바인딩한다.
	_device->GetDeviceContext()->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);
}