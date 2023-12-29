#pragma once
#include "pch.h"

using namespace DirectX;

namespace ImpGraphics
{
	struct Vertex
	{
		struct PosColor
		{
			XMFLOAT3 Pos;
			XMFLOAT4 Color;
		};

		struct PosColorTex
		{
			XMFLOAT3 Pos;
			XMFLOAT4 Color;
			XMFLOAT2 Tex;
		};

		struct QuadVertex
		{
			XMFLOAT3 Pos;
			XMFLOAT2 Tex;
		};

		struct PosNormal
		{
			XMFLOAT3 Pos;
			XMFLOAT3 Normal;
		};
	};

	class InputLayoutDesc
	{
	public:
		static const D3D11_INPUT_ELEMENT_DESC PosColor[2];
		static const D3D11_INPUT_ELEMENT_DESC PosColorTex[3];
		static const D3D11_INPUT_ELEMENT_DESC QuadVertex[2];
		static const D3D11_INPUT_ELEMENT_DESC PosNormal[2];
	};
}