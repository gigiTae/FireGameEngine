/// FbxLoader.h 
/// - FbxScene 과 FbxManager 객체를 관리합니다.
/// - Scene 안의 기타 정보를 관리하는 객체들을 관리합니다
/// 
/// 2023-12-29
///


#pragma once

#if _DEBUG
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/debug/libfbxsdk-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/debug/libxml2-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/debug/zlib-md.lib")
#else
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release/libfbxsdk-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release/libxml2-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release/zlib-md.lib")
#endif

#include "IFBXLoader.h"
#include <fbxsdk.h>

namespace FBXLoad 
{
	class MeshLoader;

	class FbxLoader : public IFBXLoader
	{
	public:
		FbxLoader();
		~FbxLoader();

		ImpMesh* GetMesh(const char* file, size_t i);
		std::vector<ImpMesh*> GetMeshAll(const char* file);
		size_t GetMeshSize(const char* file);

		// 디버깅용. 매시 목록 중 맨 처음의 메시만 읽도록 한다.
		void LoadAMeshContent(const char* file);
	private:
		void LoadFbxFile(const char* file);
		bool CreateFbxScene(const char* file);
		void LoadContent();
		void LoadContent(FbxNode* node);

		void DisplayTarget(FbxNode* pNode);
		void DisplayTransformPropagation(FbxNode* pNode);
		void DisplayGeometricTransform(FbxNode* pNode);
		void DisplayMetaData(FbxScene* pScene);

		// FBX 객체
		FbxScene* _scene{ nullptr };
		FbxManager* _manager{ nullptr };

		// Loader 객체
		MeshLoader* _meshLoader{ nullptr };
	};
}