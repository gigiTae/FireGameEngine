#pragma once

// 해당 라이브러리 관련 오류가 발생할 경우 대처법
// 1) 프로젝트 속성 설정의 구성이 Release/Debuge인지, 플랫폼이 x64 인지 확인한다 
// 2) 오토데스크 사이트에서 FBX SDK 2020.3.4 vs2022 버전을 다운 받는다 (URL: https://aps.autodesk.com/developer/overview/fbx-sdk)
// 3) FBX SDK 가 설치된 디렉터리 경로를 확인한다 (기본값 : C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022)
// 4) "추가 포함 디렉터리" 속성 에서 fbxsdk.h 가 포함된 경로를 입력한다
#if _DEBUG
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/debug/libfbxsdk-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/debug/libxml2-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/debug/zlib-md.lib")
#else
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release/libfbxsdk-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release/libxml2-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release/zlib-md.lib")
#endif

//#include <fbxsdk.h>
//#include <vector>
#include "Common.h"

namespace FBXLoad
{
	struct Scene;
	//struct SceneData;
	struct Mesh;
	struct GeometryImportSettings;

	/// <summary>
	/// FBX 데이터를 읽은 뒤 생성할 때 받았던 
	/// Secene 자료형에 저장하는 클래스
	/// </summary>
	class Parser
	{
	public:
		Parser(const char* fileName, Scene* secene/*, SceneData* sceneData*/);
		~Parser();

		void GetScene(FbxNode* root = nullptr);

		// fbx 객체가 존재하는지 확인
		constexpr bool IsValid() const;

	private:
		// 초기화
		bool InitilazeFbx();

		// 파일 로드
		void LoadFbxFile(const char* fileName);

		// 노드 가져오기
		void GetNode(FbxNode* node);
		// 버텍스 가져오기
		void GetMesh(FbxNode* node, std::vector<Mesh>& meshes);
		bool GetMeshData(FbxMesh* fbxMesh, Mesh& myMesh);
		bool GetControlPoints(FbxMesh* fbxMesh, Mesh& myMesh);
		bool GetMaterial(FbxMesh* fbxMesh, Mesh& myMesh);
		void GetVertexNormals(FbxMesh* fbxMesh, Mesh& myMesh);
		void GetTangents(FbxMesh* fbxMesh, Mesh& myMesh);
		void GetUVSet(FbxMesh* fbxMesh, Mesh& myMesh);

		// 변환 데이터 가져오기
		// 애니메이션 데이터 가져오기

		FbxManager* _fbxManager{ nullptr };
		FbxScene* _fbxScene{ nullptr };
		Scene* _scene{ nullptr };
	};
}