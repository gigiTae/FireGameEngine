/// IFBXLoader.h : Fbx Loader �� �ٸ� ���̺귯������ ������ �Լ��� ������ 
/// �������̽� Ŭ���� �Դϴ�.
///
/// 2023-12-27 ���ֿ�
/// 

#pragma once
#include "../ImpStructure/ImpMesh.h"

#pragma comment(lib, "../x64/Debug/ImpStructure.lib")

using namespace ImpStructure;

namespace FBXLoad
{
	class IFBXLoader
	{
	public:
		virtual ~IFBXLoader() {};

		virtual ImpMesh* GetMesh(const char* file, size_t i) abstract;
		virtual std::vector<ImpMesh*> GetMeshAll(const char* file) abstract;

		virtual size_t GetMeshSize(const char* file) abstract;

		// �̰͸� �ʿ��� ���� ������...?
		//GetMeshLocalPosition(size_t i);
		//GetMeshWorldPosition(size_t i);
		//GetMeshLocalPositionAll();
		//GetMeshWorldPositionAll();
	};

} // FBXLoad