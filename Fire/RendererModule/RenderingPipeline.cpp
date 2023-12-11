#include "RendererPCH.h"
#include "RenderingPipeline.h"

RendererModule::RenderingPipeline::RenderingPipeline(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	:device(device), deviceContext(deviceContext), rasterizerState{}, depthStencilState{}
	, inputLayout{}
{}

RendererModule::RenderingPipeline::~RenderingPipeline()
{
	rasterizerState[0]->Release();
	rasterizerState[1]->Release();
	depthStencilState->Release();
}

void RendererModule::RenderingPipeline::Initialize()
{
	InitializeState();
	InitializeInputLayout();
}

void RendererModule::RenderingPipeline::SetState(FILL_MODE mode)
{
	switch (mode)
	{
	case RendererModule::FILL_MODE::WIRE_FRAME:
	{
		deviceContext->RSSetState(rasterizerState[(int)FILL_MODE::SOLID]);
	}
	break;
	case RendererModule::FILL_MODE::SOLID:
	{
		deviceContext->RSSetState(rasterizerState[(int)FILL_MODE::SOLID]);
	}
	break;
	default:
		assert("여기로 올수가 없음");
		break;
	}
}

void RendererModule::RenderingPipeline::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology)
{
	deviceContext->IASetPrimitiveTopology(topology);
}

void RendererModule::RenderingPipeline::InitializeState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
	rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME; // 와이어 프레임 모드
	rasterizerDesc.CullMode = D3D11_CULL_BACK; //후면 삼각형 제외
	rasterizerDesc.FrontCounterClockwise = false; // 시계방향으로 그려지는 삼각형
	rasterizerDesc.DepthClipEnable = true; // 깊이 클리핑 활성화

	// 와이어 프레임 모드
	device->CreateRasterizerState(&rasterizerDesc, &rasterizerState[(int)FILL_MODE::WIRE_FRAME]);

	rasterizerDesc.FillMode = D3D11_FILL_SOLID;

	// 일반 그리기 모드
	device->CreateRasterizerState(&rasterizerDesc, &rasterizerState[(int)FILL_MODE::SOLID]);

	// 폰트용 DSS
	D3D11_DEPTH_STENCIL_DESC equalsDesc;
	ZeroMemory(&equalsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	equalsDesc.DepthEnable = true;
	equalsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;		// 깊이버퍼에 쓰기는 한다
	equalsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	HR(device->CreateDepthStencilState(&equalsDesc, &depthStencilState));
}

void RendererModule::RenderingPipeline::InitializeEffect()
{


}

void RendererModule::RenderingPipeline::InitializeInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC simpleDesc[] =
	{
		{"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	D3D11_INPUT_ELEMENT_DESC basicDesc[] =
	{
		{"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0,DXGI_FORMAT_R32G32B32_FLOAT,0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0,DXGI_FORMAT_R32G32_FLOAT,0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 } 
	};

}
