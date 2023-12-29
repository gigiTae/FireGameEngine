#pragma once

#include <string>

struct ID3D11Buffer;
namespace ImpStructure { struct ImpMesh; }

namespace ImpGraphics
{
	class ResourceManager;

	class Resource
	{
	public:
		Resource(ResourceManager* resourceManager) 
			: _resourceManager(resourceManager) {};
		virtual ~Resource() {};

	protected:
		ResourceManager* _resourceManager;
	};

	class VBIB : public Resource
	{
	public:
		VBIB(ResourceManager* resourceManager);
		virtual ~VBIB();

		void Load(const std::wstring& path);

		ID3D11Buffer** GetVB() { return &_VB; }
		ID3D11Buffer* GetIB() { return _IB; }
		UINT GetVertexSize() { return _vertexSize; }
		UINT GetIndexSize() { return _indexSize; }

	private:
		void CreateVBIB(ImpStructure::ImpMesh* mesh);

	private:
		UINT _vertexSize; // Vertex::xxx 의 sizeof 값
		UINT _indexSize; // 인덱스 개수 

		ID3D11Buffer* _VB;
		ID3D11Buffer* _IB;
		// 원본(e.g) vector3 array)을 저장할 까 말까
	};

	// temp
	class Shader : public Resource
	{
	public:
		Shader(ResourceManager* resourceManager);
		virtual ~Shader();

		void Load(const std::wstring& vertexShaderPath, const std::wstring& pixelShaderPath, int temp);

		void SetConstantBuffer(DirectX::XMMATRIX transformMatrix);

		ID3D11VertexShader* GetVertexShader() { return _vertexShader; }
		ID3D11PixelShader* GetPixelShader() { return _pixelShader; }
		ID3D11InputLayout* GetInputLayout() { return _inputLayout; }

	private:
		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;
		ID3D11Buffer* _constantBuffer;

		ID3D11InputLayout* _inputLayout;
	};
}