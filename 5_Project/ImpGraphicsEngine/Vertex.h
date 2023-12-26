#pragma once
#include "pch.h"

using namespace DirectX;

namespace ImpGraphics
{
	class Vertex
	{
		// helper ������Ʈ�� ���� ����
		// Axis, Grid ��
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

			/// ����� �ϳ� �߰��� ������ Vertex�� �ʿ��� ������ �þ��.
			//XMFLOAT3 Tangent; // Normal Map�� ������ ���ؼ� �ʿ��ϴ�
			// weight�� ������ 1�̹Ƿ� 3���� ������ �ȴ�.
			//XMFLOAT3 weight; 
			// ������ 4�� ���϶�� �����ϰ� �ϴ� �� �ϴ�. ���̴� �ڵ忡�� �׷��� �Ǿ�����.
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