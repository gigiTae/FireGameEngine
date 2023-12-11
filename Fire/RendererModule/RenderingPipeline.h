#pragma once

namespace RendererModule
{
	/// <summary>
	/// 랜더링파이프라인
	/// 랜더링에 필요한 설정들을 한다.
	/// </summary>
	class RenderingPipeline
	{
	public:
		RenderingPipeline(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~RenderingPipeline();
		
	public:
		void Initialize();

		/// 필요한 설정들을 나열해보자

		/// 1. 정점버퍼
		/// 2. 인덱스 버퍼
		/// 6. 변환 행렬
	
		/// RasterizerState 설정
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

