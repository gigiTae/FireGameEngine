#pragma once

namespace RendererModule
{
	/// <summary>
	/// ����������������
	/// �������� �ʿ��� �������� �Ѵ�.
	/// </summary>
	class RenderingPipeline
	{
	public:
		RenderingPipeline(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~RenderingPipeline();
		
	public:
		void Initialize();

		/// �ʿ��� �������� �����غ���

		/// 1. ��������
		/// 2. �ε��� ����
		/// 6. ��ȯ ���
	
		/// RasterizerState ����
		void SetState(FILL_MODE mode);
		void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology);

	private:
		void InitializeState();
		void InitializeEffect();
		void InitializeInputLayout();

	private:
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;

		ID3D11RasterizerState* rasterizerState[(int)FILL_MODE::END];
		ID3D11DepthStencilState* depthStencilState;
		ID3D11InputLayout* inputLayout[(int)INPUT_LAYOUT::END];

	};
}

