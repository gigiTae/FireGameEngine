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

		Vector3 _pos;		// ��ǥ���� ��ġ��(PositionL)
		float _u, _v;			// Texture
		Vector3 _normal;	// Normal

		bool m_istextureset;
		bool m_isnormalset;
	};

	struct MeshFace
	{
		MeshFace();
		~MeshFace();

		int	_vertexIndex[3]; // �� Face�� �̷�� ���ؽ��� �ε���
		//int m_TFace[3];
	};

	class Mesh
	{
		// FBX Loader���� �޾ƿͼ� 
		// �׳� ���ؽ� ���۶� �ε��� ���۸� ������ ������?
		// ���ؽ� ����� ������ �ִ´ٸ� �׸�ŭ �޸𸮰� �� �ʿ��ϰ�
		// ���ؽ� ����� GPU���� �޾ƿ��� �����ؼ� Buffer�� CPURead �������� �����ϴ� �ɼ��� ���� �ٵ� �׷��ٸ�
		// �Ƹ��� ������ ���� ������ �� ����. 
		/// �ϴ� ������, 

		/// ������ �ʿ���
		std::vector<MeshVertex*> m_meshvertex;	// ���ؽ�
		std::vector<MeshFace*> m_meshface;		// �ε���
	};
}

//�����غ��� �̰� MeshObject�� �ʿ��� �� ����.
// 	VB* _vb;
// 	IB* _ib;