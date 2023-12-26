#include "pch.h"
#include "Vertex.h"

void ImpGraphics::InputLayouts::InitAll(ID3D11Device* device)
{
	/*//
	// PosColor
	//
	D3D11_INPUT_ELEMENT_DESC PosColorDesc[2] =
	{
		{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	Effects::BasicFX->PosColorTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::PosColor, 2, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &_posColor));

	//
	// Basic32
	//
	D3D11_INPUT_ELEMENT_DESC Basic32[3] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	Effects::BasicTexFX->Light1Tech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::Basic, 3, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &_basic));*/
}

void ImpGraphics::InputLayouts::DestroyAll()
{

}
