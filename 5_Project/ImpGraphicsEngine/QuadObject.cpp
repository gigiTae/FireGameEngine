#include "pch.h"
#include "QuadObject.h"

#include "ImpDevice.h"
#include "ImpCamera.h"
#include "ImpRenderState.h"
#include "ImpRenderTarget.h"

#include "Resource.h"

ImpGraphics::QuadObject::QuadObject(std::shared_ptr<VBIB> vbib, std::shared_ptr<Shader> shader)
{
	_VBIB = vbib;
	_shader = shader;
}

ImpGraphics::QuadObject::~QuadObject()
{

}

void ImpGraphics::QuadObject::Update(ImpCamera* camera)
{

}

void ImpGraphics::QuadObject::Render(ImpDevice* device, ImpRenderState* renderState, ImpRenderTarget* rendertarget)
{
	ID3D11DeviceContext* deviceContext = device->GetDeviceContext();

	// ���÷��� ��� ���� �־�� �ұ�! ���� �ƴѰ� Ȯ���ϴ�!
	D3D11_SAMPLER_DESC samplerDesc{};
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

	// 2nd Pass
	rendertarget->Bind();
	rendertarget->Clear();

	// �Է� ���̾ƿ��� ���� �ʿ䰡 �����ϱ� �и��ؾ� �ɰ� ����.
	// �Է� ���̾ƿ�, �� ���ؽ� ���� ��ü�� �и��ϰ� ������...
	deviceContext->IASetInputLayout(_shader->GetInputLayout());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->RSSetState(renderState->_solidRS);

	UINT stride = _VBIB->GetVertexSize();
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, _VBIB->GetVB(), &stride, &offset);
	deviceContext->IASetIndexBuffer(_VBIB->GetIB(), DXGI_FORMAT_R32_UINT, 0);

	deviceContext->VSSetShader(_shader->GetVertexShader(), nullptr, 0);
	deviceContext->PSSetShader(_shader->GetPixelShader(), nullptr, 0);

	std::vector<ID3D11ShaderResourceView*> temp = rendertarget->GetShaderResourceView();
	deviceContext->PSSetShaderResources(0, 1, &temp[0]);
	deviceContext->PSSetShaderResources(1, 1, &temp[1]);

	deviceContext->DrawIndexed(6, 0, 0);

	myLinearWrapSampler->Release();
	rendertarget->Unbind();
}

void ImpGraphics::QuadObject::SetTransformMatrix(DirectX::XMMATRIX transformMatrix)
{

}
