#pragma once

namespace ImpGraphics
{
	class ImpDevice;

	// ������ ������ �� ���� Ÿ���̶� ���۵� �������� ���� Ÿ���� �����ϴ°� ����
	// �� ������ 
	class ImpRenderTarget
	{
	public:
		ImpRenderTarget(ImpDevice* device);
		~ImpRenderTarget();

		void Initialize(int width, int height);
		void OnResize(int width, int height);

		void Clear();
		void Bind();

		void FirstPassClear();
		void FirstPassBind();
		void Unbind();

		std::vector<ID3D11ShaderResourceView*> GetShaderResourceView()
		{ return _deferredShaderResourceView; }

	private:
		ImpDevice* _device;

		ID3D11RenderTargetView* _renderTargetView;		// ���� Ÿ�� ��

		size_t deferredViewSize;
		std::vector<ID3D11RenderTargetView*> _deferredRenderTargetView;
		std::vector<ID3D11ShaderResourceView*> _deferredShaderResourceView;

		ID3D11DepthStencilView* _depthStencilView;		// ���� ���Ľ� ��
	};
}