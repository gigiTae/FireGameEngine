#include "pch.h"
#include "ResourceManager.h" 
#include "Resource.h"

#include "Define.h"

//temp
#include "d3dx11effect.h"
#include <DirectXColors.h>
#include <d3dcompiler.h>

#include "ImpDevice.h"

using namespace ImpGraphics;
using namespace DirectX;

#pragma region VBIB
VBIB::VBIB(ResourceManager* resourceManager)
	:Resource(resourceManager),
	_VB(nullptr), _IB(nullptr)
{

}

VBIB::~VBIB()
{
	ReleaseCOM(_VB);
	ReleaseCOM(_IB);
}

void VBIB::Load(const std::wstring& path)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
		DirectX::XMFLOAT2 tex;
	};

	Vertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, -0.0f), XMFLOAT4((const float*)&Colors::White)  , XMFLOAT2(0.0f,1.0f) },
		{ XMFLOAT3(-1.0f, +1.0f, 0.0f), XMFLOAT4((const float*)&Colors::Black)   , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(+1.0f, +1.0f, 0.0f), XMFLOAT4((const float*)&Colors::Red)     , XMFLOAT2(1.0f,0.0f) },	// 우상 증가
		{ XMFLOAT3(+1.0f, -1.0f, 0.0f), XMFLOAT4((const float*)&Colors::Green)   , XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4((const float*)&Colors::Blue)   , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4((const float*)&Colors::Yellow) , XMFLOAT2(0.0f,1.0f) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4((const float*)&Colors::Cyan)   , XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4((const float*)&Colors::Magenta), XMFLOAT2(1.0f,0.0f) }
	};

	D3D11_BUFFER_DESC vbd{};
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * 8;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData{};
	vinitData.pSysMem = vertices;
	HR(_resourceManager->GetDevice()->GetDevice()->CreateBuffer(&vbd, &vinitData, &_VB));


	/// 인덱스 버퍼를 생성한다.

	UINT indices[] =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	D3D11_BUFFER_DESC ibd{};
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 36;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData{};
	iinitData.pSysMem = indices;
	HR(_resourceManager->GetDevice()->GetDevice()->CreateBuffer(&ibd, &iinitData, &_IB));
}
#pragma endregion VBIB

#pragma region Shader
Shader::Shader(ResourceManager* resourceManager)
	:Resource(resourceManager),
// 	_FX(nullptr),
// 	_tech(nullptr),
// 	_fxTM(nullptr),
	_inputLayout(nullptr),
	_vertexShader(nullptr),
	_pixelShader(nullptr),
	_constantBuffer(nullptr)
{

}

Shader::~Shader()
{
	ReleaseCOM(_constantBuffer);
	ReleaseCOM(_pixelShader);
	ReleaseCOM(_vertexShader);
	ReleaseCOM(_inputLayout)
/*	ReleaseCOM(_FX);*/
}

void Shader::Load(const std::wstring& vertexShaderPath, const std::wstring& pixelShaderPath)
{
	/*std::ifstream fin(path, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, _resourceManager->GetDevice()->GetDevice(), &_FX));

	_tech = _FX->GetTechniqueByName("ColorTech");
	_fxTM = _FX->GetVariableByName("gWorldViewProj")->AsMatrix();

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	_tech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(_resourceManager->GetDevice()->GetDevice()->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &_inputLayout));*/

	struct TransformMatrix
	{
		XMFLOAT4X4 transform;
	};

	ID3D11Device* device = _resourceManager->GetDevice()->GetDevice();

	// 마지막 nullptr은 에러메시지를 받을 때 포인터를 집어넣는 것이다
	ID3D10Blob* vertexShaderBuffer = nullptr;
	D3DCompileFromFile(vertexShaderPath.c_str(), nullptr, nullptr, "VS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, nullptr);

	ID3D10Blob* pixelShaderBuffer = nullptr;
	D3DCompileFromFile(pixelShaderPath.c_str(), nullptr, nullptr, "PS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, nullptr);

	device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), nullptr, &_vertexShader);

	device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), 
		pixelShaderBuffer->GetBufferSize(), nullptr, &_pixelShader);

	//입력 레이아웃 생성
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	device->CreateInputLayout(vertexDesc, 3, vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), &_inputLayout);

	ReleaseCOM(vertexShaderBuffer);
	ReleaseCOM(pixelShaderBuffer);

	D3D11_BUFFER_DESC constantBuffer;
	constantBuffer.Usage = D3D11_USAGE_DYNAMIC;
	constantBuffer.ByteWidth = sizeof(TransformMatrix);
	constantBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBuffer.MiscFlags = 0;
	constantBuffer.StructureByteStride = 0;

	// 상수 버퍼 포인터를 만들어 이 클래스에서 정점 쉐이더 상수 버퍼에 접근할 수 있게 한다.
	device->CreateBuffer(&constantBuffer, nullptr, &_constantBuffer);
}

void Shader::SetConstantBuffer(XMMATRIX transformMatrix)
{
	ID3D11DeviceContext* deviceContext = _resourceManager->GetDevice()->GetDeviceContext();

	struct TransformMatrix
	{
		XMFLOAT4X4 transform;
	};

	transformMatrix = XMMatrixTranspose(transformMatrix);

	// 상수 버퍼의 내용을 쓸 수 있도록 잠근다.
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	deviceContext->Map(_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// 상수 버퍼의 데이터에 대한 포인터를 가져온다.
	TransformMatrix* dataPtr = reinterpret_cast<TransformMatrix*>(mappedResource.pData);

	// 상수 버퍼에 행렬을 복사한다.
	XMStoreFloat4x4(&dataPtr->transform, transformMatrix);

	// 상수 버퍼의 잠금을 푼다.
	deviceContext->Unmap(_constantBuffer, 0);

	// 정점 쉐이더에서의 상수 버퍼의 위치를 설정한다.
	unsigned bufferOffset = 0;

	// 마지막으로 정점 쉐이더의 상수 버퍼를 바뀐 값으로 바꾼다.
	deviceContext->VSSetConstantBuffers(bufferOffset, 1, &_constantBuffer);
}

#pragma endregion Shader