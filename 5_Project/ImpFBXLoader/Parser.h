#pragma once

// �ش� ���̺귯�� ���� ������ �߻��� ��� ��ó��
// 1) ������Ʈ �Ӽ� ������ ������ Release/Debuge����, �÷����� x64 ���� Ȯ���Ѵ� 
// 2) ���䵥��ũ ����Ʈ���� FBX SDK 2020.3.4 vs2022 ������ �ٿ� �޴´� (URL: https://aps.autodesk.com/developer/overview/fbx-sdk)
// 3) FBX SDK �� ��ġ�� ���͸� ��θ� Ȯ���Ѵ� (�⺻�� : C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022)
// 4) "�߰� ���� ���͸�" �Ӽ� ���� fbxsdk.h �� ���Ե� ��θ� �Է��Ѵ�
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
	/// FBX �����͸� ���� �� ������ �� �޾Ҵ� 
	/// Secene �ڷ����� �����ϴ� Ŭ����
	/// </summary>
	class Parser
	{
	public:
		Parser(const char* fileName, Scene* secene/*, SceneData* sceneData*/);
		~Parser();

		void GetScene(FbxNode* root = nullptr);

		// fbx ��ü�� �����ϴ��� Ȯ��
		constexpr bool IsValid() const;

	private:
		// �ʱ�ȭ
		bool InitilazeFbx();

		// ���� �ε�
		void LoadFbxFile(const char* fileName);

		// ��� ��������
		void GetNode(FbxNode* node);
		// ���ؽ� ��������
		void GetMesh(FbxNode* node, std::vector<Mesh>& meshes);
		bool GetMeshData(FbxMesh* fbxMesh, Mesh& myMesh);
		bool GetControlPoints(FbxMesh* fbxMesh, Mesh& myMesh);
		bool GetMaterial(FbxMesh* fbxMesh, Mesh& myMesh);
		void GetVertexNormals(FbxMesh* fbxMesh, Mesh& myMesh);
		void GetTangents(FbxMesh* fbxMesh, Mesh& myMesh);
		void GetUVSet(FbxMesh* fbxMesh, Mesh& myMesh);

		// ��ȯ ������ ��������
		// �ִϸ��̼� ������ ��������

		FbxManager* _fbxManager{ nullptr };
		FbxScene* _fbxScene{ nullptr };
		Scene* _scene{ nullptr };
	};
}