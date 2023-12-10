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

		/// 필요한 설정들을 나열해보자

		/// 1. 정점버퍼
		/// 2. 인덱스 버퍼
		/// 4. InputLayout
		/// 5. Effect
		/// 6. 변환 행렬
	
		/// 3. RasterizerState

	private:
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
	};
}

