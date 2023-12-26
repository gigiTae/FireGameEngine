#include "pch.h"
#include "ImpRenderState.h"

#include "define.h"

ImpGraphics::ImpRenderState::ImpRenderState()
	:_wireframeRS(nullptr),
	_solidRS(nullptr),
	_normalDSS(nullptr)
{
	
}

ImpGraphics::ImpRenderState::~ImpRenderState()
{
	ReleaseCOM(_wireframeRS);
	ReleaseCOM(_solidRS);
	ReleaseCOM(_normalDSS);
}

void ImpGraphics::ImpRenderState::Initialize(ID3D11Device* device)
{
	/// Render State

	/// Rasterizer State
	// 솔리드
	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_NONE;
	solidDesc.FrontCounterClockwise = false;
	solidDesc.DepthClipEnable = true;
	HR(device->CreateRasterizerState(&solidDesc, &_solidRS));

	// 와이어
	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_NONE;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;
	HR(device->CreateRasterizerState(&wireframeDesc, &_wireframeRS));


	/// Depth-Stencil State
	// 폰트용 DSS
	D3D11_DEPTH_STENCIL_DESC equalsDesc;
	ZeroMemory(&equalsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	equalsDesc.DepthEnable = true;
	equalsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;		// 깊이버퍼에 쓰기는 한다
	equalsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	HR(device->CreateDepthStencilState(&equalsDesc, &_normalDSS));
}