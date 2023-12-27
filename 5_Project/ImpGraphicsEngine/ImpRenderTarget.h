#pragma once

namespace ImpGraphics
{
	class ImpDevice;

	class ImpRenderTarget
	{
	public:
		ImpRenderTarget(ImpDevice* device);
		~ImpRenderTarget();

		void Initialize(int width, int height);
		void OnResize(int width, int height);

		void Clear();
		void FirstPassClear();
		void FirstPassBind();
		void Bind();

		std::vector<ID3D11ShaderResourceView*> GetShaderResourceView()
		{ return _deferredShaderResourceView; }

	private:
		ImpDevice* _device;

		ID3D11RenderTargetView* _renderTargetView;		// ·£´õ Å¸°Ù ºä

		size_t deferredViewSize;
		std::vector<ID3D11RenderTargetView*> _deferredRenderTargetView;
		std::vector<ID3D11ShaderResourceView*> _deferredShaderResourceView;

		ID3D11DepthStencilView* _depthStencilView;		// µª½º ½ºÅÄ½Ç ºä
	};
}