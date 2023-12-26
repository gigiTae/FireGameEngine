#pragma once

struct ID3D11Device;

namespace ImpGraphics
{
	class ImpRenderState
	{
	public:
		ImpRenderState();
		~ImpRenderState();

		void Initialize(ID3D11Device* device);

		//temp
	public:
		ID3D11RasterizerState* _wireframeRS;
		ID3D11RasterizerState* _solidRS;
		ID3D11DepthStencilState* _normalDSS;		// 폰트때문에 뎁스스탠실 스테이트가 강제가 됐다.
	};
}