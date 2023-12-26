#include "pch.h"
#include "MeshObject.h"

#include "ImpDevice.h"
#include "ImpCamera.h"
#include "ImpRenderState.h"

#include "Resource.h"
#include "d3dx11effect.h"

using namespace ImpGraphics;

MeshObject::MeshObject(std::shared_ptr<VBIB> vbib, std::shared_ptr<Shader> shader)
{
	_VBIB = vbib;
	_shader = shader;
}

MeshObject::~MeshObject()
{

}

void MeshObject::Update(ImpCamera* camera)
{
	_viewTM = camera->GetViewTM();
	_projTM = camera->GetProjTM();
}

void MeshObject::Render(ImpDevice* device, ImpRenderState* renderState)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
	};

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
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX worldViewProj = world * view * proj;

	deviceContext->VSSetShader(_shader->GetVertexShader(), nullptr, 0);
	deviceContext->PSSetShader(_shader->GetPixelShader(), nullptr, 0);

	_shader->SetConstantBuffer(worldViewProj);

	deviceContext->DrawIndexed(36, 0, 0);
	//_shader->GetFxTM()->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	//D3DX11_TECHNIQUE_DESC techDesc;
	//_shader->GetTech()->GetDesc(&techDesc);

// 	for (UINT p = 0; p < techDesc.Passes; ++p)
// 	{
// 		//_shader->GetTech()->GetPassByIndex(p)->Apply(0, deviceContext);
// 		deviceContext->DrawIndexed(36, 0, 0);
// 	}
}