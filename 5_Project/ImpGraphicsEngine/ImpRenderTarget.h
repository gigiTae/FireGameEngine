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
		void Bind();

	private:
		ImpDevice* _device;

		ID3D11RenderTargetView* _renderTargetView;		// ·£´õ Å¸°Ù ºä
		ID3D11DepthStencilView* _depthStencilView;		// µª½º ½ºÅÄ½Ç ºä
	};
}