#pragma once
#include "pch.h"

using namespace DirectX;

namespace ImpGraphics
{
	class Vertex
	{
		// helper 오브젝트를 위해 존재
		// Axis, Grid 등
		struct PosColor
		{
			XMFLOAT3 Pos;
			XMFLOAT4 Color;
		};

		struct Basic
		{
			XMFLOAT3 Pos;
			XMFLOAT3 Normal;
			XMFLOAT2 Tex;

			/// 기술을 하나 추가할 때마다 Vertex에 필요한 정보가 늘어난다.
			//XMFLOAT3 Tangent; // Normal Map을 입히기 위해서 필요하다
			// weight의 총합이 1이므로 3개만 보내면 된다.
			//XMFLOAT3 weight; 
			// 무조건 4개 이하라고 가정하고 하는 듯 하다. 셰이더 코드에도 그렇게 되어있음.
			//UINT32 BoneIndices[4];
		};
	};

	class InputLayouts
	{
	public:
		void InitAll(ID3D11Device* device);
		void DestroyAll();

		ID3D11InputLayout* _posColor;
		ID3D11InputLayout* _basic;
	};
}