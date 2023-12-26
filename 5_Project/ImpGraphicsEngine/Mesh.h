#pragma once
#include "pch.h"
#include "../ImpStructure/ImpMath.h"

using namespace ImpMath;

namespace ImpGraphics
{
	struct MeshVertex
	{
		MeshVertex();
		~MeshVertex();

		Vector3 _pos;		// 좌표상의 위치값(PositionL)
		float _u, _v;			// Texture
		Vector3 _normal;	// Normal

		bool m_istextureset;
		bool m_isnormalset;
	};

	struct MeshFace
	{
		MeshFace();
		~MeshFace();

		int	_vertexIndex[3]; // 이 Face를 이루는 버텍스의 인덱스
		//int m_TFace[3];
	};

	class Mesh
	{
		// FBX Loader에서 받아와서 
		// 그냥 버텍스 버퍼랑 인덱스 버퍼를 가지고 있을까?
		// 버텍스 목록을 가지고 있는다면 그만큼 메모리가 더 필요하고
		// 버텍스 목록을 GPU에서 받아오게 설정해서 Buffer를 CPURead 가능으로 설정하는 옵션이 있을 텐데 그렇다면
		// 아마도 성능은 조금 떨어질 것 같다. 
		/// 일단 포지션, 

		/// 무조건 필요함
		std::vector<MeshVertex*> m_meshvertex;	// 버텍스
		std::vector<MeshFace*> m_meshface;		// 인덱스
	};
}

//생각해보면 이건 MeshObject에 필요한 거 같다.
// 	VB* _vb;
// 	IB* _ib;