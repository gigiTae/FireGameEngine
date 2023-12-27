#include "pch.h"
#include "MeshObject.h"

#include "ImpDevice.h"
#include "ImpCamera.h"
#include "ImpRenderState.h"
#include "ImpRenderTarget.h"

#include "Resource.h"
#include "d3dx11effect.h"

using namespace ImpGraphics;

MeshObject::MeshObject(std::shared_ptr<VBIB> vbib, std::shared_ptr<Shader> shader)
	:_shader2(nullptr)
{
	_VBIB = vbib;
	_shader = shader;
}

MeshObject::MeshObject(std::shared_ptr<VBIB> vbib, std::shared_ptr<Shader> shader, std::shared_ptr<Shader> shader2)
{
	_VBIB = vbib;
	_shader = shader;
	_shader2 = shader2;
}

MeshObject::~MeshObject()
{

}

void MeshObject::Update(ImpCamera* camera)
{
	_viewTM = camera->GetViewTM();
	_projTM = camera->GetProjTM();
}

void MeshObject::Render(ImpDevice* device, ImpRenderState* renderState, ImpRenderTarget* rendertarget)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
		DirectX::XMFLOAT2 tex;
	};

	rendertarget->FirstPassBind();
	rendertarget->FirstPassClear();

	ID3D11DeviceContext* deviceContext = device->GetDeviceContext();

	deviceContext->IASetInputLayout(_shader->GetInputLayout());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->RSSetState(renderState->_solidRS);
	
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, _VBIB->GetVB(), &stride, &offset);
	deviceContext->IASetIndexBuffer(_VBIB->GetIB(), DXGI_FORMAT_R32_UINT, 0);

	DirectX::XMMATRIX view = XMLoadFloat4x4(&_viewTM);
	DirectX::XMMATRIX proj = XMLoadFloat4x4(&_projTM);
	DirectX::XMMATRIX world = XMLoadFloat4x4(&_worldTM);
	DirectX::XMMATRIX worldViewProj = world * view * proj;

	deviceContext->VSSetShader(_shader->GetVertexShader(), nullptr, 0);
	deviceContext->PSSetShader(_shader->GetPixelShader(), nullptr, 0);

	_shader->SetConstantBuffer(worldViewProj);

	deviceContext->DrawIndexed(36, 0, 0);









	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = -FLT_MAX;
	samplerDesc.MaxLOD = FLT_MAX;

	ID3D11SamplerState* myLinearWrapSampler;
	HRESULT hr = device->GetDevice()->CreateSamplerState(&samplerDesc, &myLinearWrapSampler);
	deviceContext->PSSetSamplers(0, 1, &myLinearWrapSampler);

	rendertarget->Bind();
	rendertarget->Clear();

	deviceContext->IASetInputLayout(_shader->GetInputLayout());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->RSSetState(renderState->_solidRS);
	deviceContext->IASetVertexBuffers(0, 1, _VBIB->GetVB(), &stride, &offset);
	deviceContext->IASetIndexBuffer(_VBIB->GetIB(), DXGI_FORMAT_R32_UINT, 0);

	deviceContext->VSSetShader(_shader2->GetVertexShader(), nullptr, 0);
	deviceContext->PSSetShader(_shader2->GetPixelShader(), nullptr, 0);

	std::vector<ID3D11ShaderResourceView*> temp = rendertarget->GetShaderResourceView();
	deviceContext->PSSetShaderResources(0, 1, &temp[0]);
	deviceContext->PSSetShaderResources(1, 1, &temp[1]);

	deviceContext->DrawIndexed(36, 0, 0);

	ID3D11ShaderResourceView* pSRV = NULL;
	deviceContext->PSSetShaderResources(0, 1, &pSRV);

	myLinearWrapSampler->Release();

	pSRV = NULL;
	deviceContext->PSSetShaderResources(1, 1, &pSRV);
	//_shader->GetFxTM()->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	//D3DX11_TECHNIQUE_DESC techDesc;
	//_shader->GetTech()->GetDesc(&techDesc);

// 	for (UINT p = 0; p < techDesc.Passes; ++p)
// 	{
// 		//_shader->GetTech()->GetPassByIndex(p)->Apply(0, deviceContext);
// 		deviceContext->DrawIndexed(36, 0, 0);
// 	}
}

void MeshObject::SetTransformMatrix(DirectX::XMMATRIX transformMatrix)
{
	XMStoreFloat4x4(&_worldTM, transformMatrix);
}