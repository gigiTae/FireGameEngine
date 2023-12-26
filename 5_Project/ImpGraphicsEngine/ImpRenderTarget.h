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

		ID3D11RenderTargetView* _renderTargetView;		// ���� Ÿ�� ��
		ID3D11DepthStencilView* _depthStencilView;		// ���� ���Ľ� ��
	};
}