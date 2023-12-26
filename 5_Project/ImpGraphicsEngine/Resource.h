#pragma once

#include <string>

struct ID3D11Buffer;

struct ID3DX11Effect;
struct ID3DX11EffectTechnique;
struct ID3DX11EffectMatrixVariable;

namespace ImpGraphics
{
	class ResourceManager;

	class Resource
	{
	public:
		Resource(ResourceManager* resourceManager) 
			: _resourceManager(resourceManager) {};
		virtual ~Resource() {};

		virtual void Load(const std::wstring& path) abstract;

	protected:
		ResourceManager* _resourceManager;
	};

	class VBIB : public Resource
	{
	public:
		VBIB(ResourceManager* resourceManager);
		virtual ~VBIB();

		virtual void Load(const std::wstring& path) override;

		ID3D11Buffer** GetVB() { return &_VB; }
		ID3D11Buffer* GetIB() { return _IB; }

	private:
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

		virtual void Load(const std::wstring& path) override;

		void SetConstantBuffer(DirectX::XMMATRIX transformMatrix);

// 		ID3DX11Effect* GetFX() { return _FX; }
// 		ID3DX11EffectTechnique* GetTech() { return _tech; }
// 		ID3DX11EffectMatrixVariable* GetFxTM() { return _fxTM; }

		ID3D11VertexShader* GetVertexShader() { return _vertexShader; }
		ID3D11PixelShader* GetPixelShader() { return _pixelShader; }
		ID3D11InputLayout* GetInputLayout() { return _inputLayout; }

	private:
// 		ID3DX11Effect* _FX;								// 이펙트
// 		ID3DX11EffectTechnique* _tech;					// 테크
// 		ID3DX11EffectMatrixVariable* _fxTM;

		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;
		ID3D11Buffer* _constantBuffer;

		ID3D11InputLayout* _inputLayout;
	};
}