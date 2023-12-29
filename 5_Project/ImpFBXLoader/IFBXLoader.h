/// IFBXLoader.h : Fbx Loader 가 다른 라이브러리에게 제공할 함수를 정의한 
/// 인터페이스 클레스 입니다.
///
/// 2023-12-27 김주영
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

		// 이것만 필요할 일이 있을까...?
		//GetMeshLocalPosition(size_t i);
		//GetMeshWorldPosition(size_t i);
		//GetMeshLocalPositionAll();
		//GetMeshWorldPositionAll();
	};

} // FBXLoad