#include "pch.h"
#include "ResourceManager.h" 
#include "Resource.h"

#include "Define.h"

//temp
#include "d3dx11effect.h"
#include <DirectXColors.h>
#include <d3dcompiler.h>

#include "ImpDevice.h"
#include "ImpLoader.h"
#include "../ImpFBXLoader/IFBXLoader.h"

#include "../ImpStructure/ImpMesh.h"

#include "Vertex.h"

using namespace ImpGraphics;
using namespace ImpStructure;
using namespace DirectX;

#pragma region VBIB
VBIB::VBIB(ResourceManager* resourceManager)
	:Resource(resourceManager),
	_VB(nullptr), _IB(nullptr),
	_vertexSize(0), _indexSize(0)
{

}

VBIB::~VBIB()
{
	ReleaseCOM(_VB);
	ReleaseCOM(_IB);
}

void VBIB::Load(const std::wstring& path)
{
	// 만약 3글자 이상의 확장자를 쓸 거라면 마지막 / 위치를 찾아서 거기부터 잘라야 함
	ImpStructure::ImpMesh* mesh = nullptr;

	std::wstring fileExtension = path.substr(path.length() - 3);
	if (fileExtension._Equal(L"imp"))
	{
		mesh = _resourceManager->GetImpLoader()->GetMesh(path);
	}
	else if (fileExtension._Equal(L"fbx"))
	{
		const wchar_t* pathWchar = path.c_str();
		wchar_t* wchar = const_cast<wchar_t*>(pathWchar);

		char* pStr;
		int strSize = WideCharToMultiByte(CP_ACP, 0, wchar, -1, NULL, 0, NULL, NULL);
		pStr = new char[strSize];
		WideCharToMultiByte(CP_ACP, 0, wchar, -1, pStr, strSize, 0, 0);

		mesh = _resourceManager->GetFBXLoader()->GetMesh(pStr, 0);
	}

	if (mesh != nullptr)
	{
		CreateVBIB(mesh);
	}
	else
	{
		MessageBox(NULL, L"Mesh가 nullptr입니다.", L"에러", MB_ICONERROR);
	}
	delete mesh;
}

void VBIB::CreateVBIB(ImpStructure::ImpMesh* mesh)
{
	/// 버텍스 버퍼 생성
	if (mesh->_hasColor && mesh->_hasTexture)
	{
		std::vector<Vertex::PosColorTex> vertices;
		Vertex::PosColorTex temp{};
		_vertexSize = sizeof(Vertex::PosColorTex);

		for (UINT i = 0; i < mesh->_meshVertex.size(); i++)
		{
			temp.Pos.x = mesh->_meshVertex[i]->_localPos.x;
			temp.Pos.y = mesh->_meshVertex[i]->_localPos.y;
			temp.Pos.z = mesh->_meshVertex[i]->_localPos.z;

			temp.Color.x = mesh->_meshVertex[i]->_color.x;
			temp.Color.y = mesh->_meshVertex[i]->_color.y;
			temp.Color.z = mesh->_meshVertex[i]->_color.z;
			temp.Color.w = mesh->_meshVertex[i]->_color.w;

			temp.Tex.x = mesh->_meshVertex[i]->_u;
			temp.Tex.y = mesh->_meshVertex[i]->_v;

			vertices.emplace_back(temp);
		}

		D3D11_BUFFER_DESC vbd{};
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = _vertexSize * vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vinitData{};
		vinitData.pSysMem = &vertices[0];
		HR(_resourceManager->GetDevice()->GetDevice()->CreateBuffer(&vbd, &vinitData, &_VB));
	}

	else if (mesh->_hasTexture)
	{
		std::vector<Vertex::QuadVertex> vertices;
		Vertex::QuadVertex temp{};
		_vertexSize = sizeof(Vertex::QuadVertex);

		for (UINT i = 0; i < mesh->_meshVertex.size(); i++)
		{
			temp.Pos.x = mesh->_meshVertex[i]->_localPos.x;
			temp.Pos.y = mesh->_meshVertex[i]->_localPos.y;
			temp.Pos.z = mesh->_meshVertex[i]->_localPos.z;

			temp.Tex.x = mesh->_meshVertex[i]->_u;
			temp.Tex.y = mesh->_meshVertex[i]->_v;

			vertices.emplace_back(temp);
		}

		D3D11_BUFFER_DESC vbd{};
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Vertex::QuadVertex) * vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vinitData{};
		vinitData.pSysMem = &vertices[0];
		HR(_resourceManager->GetDevice()->GetDevice()->CreateBuffer(&vbd, &vinitData, &_VB));
	}

	else if (mesh->_hasNormal)
	{
		std::vector<Vertex::PosNormal> vertices;
		Vertex::PosNormal temp{};
		_vertexSize = sizeof(Vertex::PosNormal);

		for (size_t i = 0; i < mesh->_meshVertex.size(); i++)
		{
			temp.Pos.x = mesh->_meshVertex[i]->_localPos.x;
			temp.Pos.y = mesh->_meshVertex[i]->_localPos.y;
			temp.Pos.z = mesh->_meshVertex[i]->_localPos.z;

			temp.Normal.x = mesh->_meshVertex[i]->_normal.x;
			temp.Normal.y = mesh->_meshVertex[i]->_normal.y;
			temp.Normal.z = mesh->_meshVertex[i]->_normal.z;

			vertices.emplace_back(temp);
		}

		D3D11_BUFFER_DESC vbd{};
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Vertex::PosNormal) * vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vinitData{};
		vinitData.pSysMem = &vertices[0];
		HR(_resourceManager->GetDevice()->GetDevice()->CreateBuffer(&vbd, &vinitData, &_VB));
	}

	/// 인덱스 버퍼를 생성한다.
	std::vector<UINT> indices;
	for (UINT i = 0; i < mesh->_meshFace.size(); i++)
	{
		indices.emplace_back(mesh->_meshFace[i]->vertexIndex[0]);
		indices.emplace_back(mesh->_meshFace[i]->vertexIndex[1]);
		indices.emplace_back(mesh->_meshFace[i]->vertexIndex[2]);
	}

	_indexSize = indices.size();

	D3D11_BUFFER_DESC ibd{};
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * indices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData{};
	iinitData.pSysMem = &indices[0];
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

void Shader::Load(const std::wstring& vertexShaderPath, const std::wstring& pixelShaderPath, int temp)
{
	if (temp == 0)
	{
		struct TransformMatrix
		{
			XMFLOAT4X4 transform;
		};

		ID3D11Device* device = _resourceManager->GetDevice()->GetDevice();

		// 마지막 nullptr은 에러메시지를 받을 때 포인터를 집어넣는 것이다
		ID3D10Blob* vertexShaderBuffer = nullptr;
		D3DCompileFromFile(vertexShaderPath.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0,
			&vertexShaderBuffer, nullptr);

		ID3D10Blob* pixelShaderBuffer = nullptr;
		D3DCompileFromFile(pixelShaderPath.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0,
			&pixelShaderBuffer, nullptr);

		device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(), nullptr, &_vertexShader);

		device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
			pixelShaderBuffer->GetBufferSize(), nullptr, &_pixelShader);

		device->CreateInputLayout(InputLayoutDesc::PosNormal, 2, vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(), &_inputLayout);

		ReleaseCOM(vertexShaderBuffer);
		ReleaseCOM(pixelShaderBuffer);

		D3D11_BUFFER_DESC constantBuffer{};
		constantBuffer.Usage = D3D11_USAGE_DYNAMIC;
		constantBuffer.ByteWidth = sizeof(TransformMatrix);
		constantBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBuffer.MiscFlags = 0;
		constantBuffer.StructureByteStride = 0;

		// 상수 버퍼 포인터를 만들어 이 클래스에서 정점 쉐이더 상수 버퍼에 접근할 수 있게 한다.
		device->CreateBuffer(&constantBuffer, nullptr, &_constantBuffer);
	}
	else
	{
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

		device->CreateInputLayout(InputLayoutDesc::QuadVertex, 2, vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(), &_inputLayout);

		ReleaseCOM(vertexShaderBuffer);
		ReleaseCOM(pixelShaderBuffer);

		D3D11_BUFFER_DESC constantBuffer{};
		constantBuffer.Usage = D3D11_USAGE_DYNAMIC;
		constantBuffer.ByteWidth = sizeof(TransformMatrix);
		constantBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBuffer.MiscFlags = 0;
		constantBuffer.StructureByteStride = 0;

		// 상수 버퍼 포인터를 만들어 이 클래스에서 정점 쉐이더 상수 버퍼에 접근할 수 있게 한다.
		device->CreateBuffer(&constantBuffer, nullptr, &_constantBuffer);
	}
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