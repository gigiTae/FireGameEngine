#include "pch.h"
#include "MeshObject.h"

#include "ImpDevice.h"
#include "ImpCamera.h"
#include "ImpRenderState.h"
#include "ImpRenderTarget.h"

#include "Resource.h"

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

void MeshObject::Render(ImpDevice* device, ImpRenderState* renderState, ImpRenderTarget* rendertarget)
{
	// 1st Pass
	ID3D11DeviceContext* deviceContext = device->GetDeviceContext();

	deviceContext->IASetInputLayout(_shader->GetInputLayout());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->RSSetState(renderState->_solidRS);
	
	UINT stride = _VBIB->GetVertexSize();
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

	deviceContext->DrawIndexed(_VBIB->GetIndexSize(), 0, 0);
}

void MeshObject::SetTransformMatrix(DirectX::XMMATRIX transformMatrix)
{
	XMStoreFloat4x4(&_worldTM, transformMatrix);
}