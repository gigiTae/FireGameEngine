#include "FbxLoader.h"
#include "MeshLoader.h"

FBXLoad::FbxLoader::FbxLoader()
	: _scene()
	, _manager(FbxManager::Create())
	, _meshLoader(new FBXLoad::MeshLoader(_manager))
{
	if (!_manager)
	{
		FBXSDK_printf("오류: 《FbxManager》를 만들 수 없음.\n\n");
		exit(1);

	}
	else FBXSDK_printf("\n>> Autodesk FBX SDK 버전: \"%s\"\n", _manager->GetVersion());

	// IO 설정 객체 생성 및 초기화
	FbxIOSettings* ios{ FbxIOSettings::Create(_manager, IOSROOT) };
	_manager->SetIOSettings(ios);

}

FBXLoad::FbxLoader::~FbxLoader()
{
	delete _meshLoader;

	_scene->Destroy();
	if (_manager) _manager->Destroy();
}

ImpMesh* FBXLoad::FbxLoader::GetMesh(const char* file, size_t i)
{
	LoadFbxFile(file);
	return _meshLoader->GetMesh(i);
}

std::vector<ImpMesh*> FBXLoad::FbxLoader::GetMeshAll(const char* file)
{
	LoadFbxFile(file);
	return _meshLoader->GetMeshAll();
}

size_t FBXLoad::FbxLoader::GetMeshSize(const char* file)
{
	LoadFbxFile(file);
	return _meshLoader->GetMeshSize();
}

void FBXLoad::FbxLoader::LoadAMeshContent(const char* file)
{
	assert(_manager && file);
	FBXSDK_printf("\n>> 파일 이름: \"%s\" \n", file);

	if (CreateFbxScene(file))
	{
		LoadContent();
	}
}

void FBXLoad::FbxLoader::LoadFbxFile(const char* file)
{
	assert(_manager && file);
	FBXSDK_printf("\n>> 파일 이름: \"%s\" \n", file);

	if (CreateFbxScene(file))
	{
		// 씬에서 얻을 수 있는 것들

		// MetaData
		// GlobalLightSettings
		// GlobalCameraSettings
		// GlobalTimeSettings
		// Hierarchy
		// Content
		LoadContent();
		// Pose
		// Animation
		// yGenericInfo
	}

	FbxNode* node{ _scene->GetRootNode() };
	const int numChild{ node->GetChildCount() };
	LoadContent(node->GetChild(0));
}

bool FBXLoad::FbxLoader::CreateFbxScene(const char* file)
{
	// importer 생성
	FbxImporter* fbxImporter{ FbxImporter::Create(_manager, "Importer") };

	// 해당 파일이 없으면 다음과 같은 오류 발생
	if (!fbxImporter->Initialize(file, -1, _manager->GetIOSettings()))
	{
		FBXSDK_printf("%s 파일을 여는데 실패했습니다.\n\n", file);
		FBXSDK_printf("오류 보고: %s\n\n", fbxImporter->GetStatus().GetErrorString());
		exit(-1);
		return false;
	}

	if (_scene)
	{
		_scene->Destroy();
	}

	_scene = FbxScene::Create(_manager, "Importer Scene");
	FBXSDK_printf("\n>> Scene name: \"%s\"\n\n", _scene->GetName());

	if (!_scene)
	{
		FBXSDK_printf("오류: 《FbxScene》을 만들 수 없음!\n\n");
		exit(1);
		return false;
	}

	// importer 에게 씬 전달
	if (!fbxImporter->Import(_scene))
	{
		printf("오류 보고: %s\n\n", fbxImporter->GetStatus().GetErrorString());
		exit(-1);
		return false;
	}

	// importer 삭제
	fbxImporter->Destroy();

	return true;
}

void FBXLoad::FbxLoader::LoadContent()
{
	int i{ 0 };
	FbxNode* node{ _scene->GetRootNode() };
	const int numChild{ node->GetChildCount() };

	if (node)
	{
		for (i = 0; i < numChild; i++)
		{
			LoadContent(node->GetChild(i));
		}
	}
}

void FBXLoad::FbxLoader::LoadContent(FbxNode* pNode)
{
	FbxNodeAttribute::EType lAttributeType;
	int i{ 0 };

	if (pNode->GetNodeAttribute() == NULL)
	{
		FBXSDK_printf("NULL Node Attribute\n\n");
	}
	else
	{
		lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());
		
		switch (lAttributeType)
		{
		case fbxsdk::FbxNodeAttribute::eUnknown:
			break;
		case fbxsdk::FbxNodeAttribute::eNull:
			break;
		case fbxsdk::FbxNodeAttribute::eMarker:
			break;
		case fbxsdk::FbxNodeAttribute::eSkeleton:
			break;
		case fbxsdk::FbxNodeAttribute::eMesh:
			_meshLoader->LoadMesh(pNode);
			break;
		case fbxsdk::FbxNodeAttribute::eNurbs:
			break;
		case fbxsdk::FbxNodeAttribute::ePatch:
			break;
		case fbxsdk::FbxNodeAttribute::eCamera:
			break;
		case fbxsdk::FbxNodeAttribute::eCameraStereo:
			break;
		case fbxsdk::FbxNodeAttribute::eCameraSwitcher:
			break;
		case fbxsdk::FbxNodeAttribute::eLight:
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalReference:
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalMarker:
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsCurve:
			break;
		case fbxsdk::FbxNodeAttribute::eTrimNurbsSurface:
			break;
		case fbxsdk::FbxNodeAttribute::eBoundary:
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsSurface:
			break;
		case fbxsdk::FbxNodeAttribute::eShape:
			break;
		case fbxsdk::FbxNodeAttribute::eLODGroup:
			break;
		case fbxsdk::FbxNodeAttribute::eSubDiv:
			break;
		case fbxsdk::FbxNodeAttribute::eCachedEffect:
			break;
		case fbxsdk::FbxNodeAttribute::eLine:
			break;
		default:
			break;
		}
	}

	//DisplayUserProperties(pNode);
	DisplayTarget(pNode);
	//DisplayPivotsAndLimits(pNode);
	DisplayTransformPropagation(pNode);
	DisplayGeometricTransform(pNode);

	for (i = 0; i < pNode->GetChildCount(); i++)
	{
		LoadContent(pNode->GetChild(i));
	}
}

void FBXLoad::FbxLoader::DisplayTarget(FbxNode* pNode)
{
	if (pNode->GetTarget() != NULL)
	{
		FBXSDK_printf("    Target Name: %s\n", (char*)pNode->GetTarget()->GetName());
	}
}

void FBXLoad::FbxLoader::DisplayTransformPropagation(FbxNode* pNode)
{
	FBXSDK_printf("    Transformation Propagation\n");

	// 
	// Rotation Space
	//
	EFbxRotationOrder lRotationOrder;
	pNode->GetRotationOrder(FbxNode::eSourcePivot, lRotationOrder);

	FBXSDK_printf("        Rotation Space: ");

	switch (lRotationOrder)
	{
	case eEulerXYZ:
		FBXSDK_printf("Euler XYZ\n");
		break;
	case eEulerXZY:
		FBXSDK_printf("Euler XZY\n");
		break;
	case eEulerYZX:
		FBXSDK_printf("Euler YZX\n");
		break;
	case eEulerYXZ:
		FBXSDK_printf("Euler YXZ\n");
		break;
	case eEulerZXY:
		FBXSDK_printf("Euler ZXY\n");
		break;
	case eEulerZYX:
		FBXSDK_printf("Euler ZYX\n");
		break;
	case eSphericXYZ:
		FBXSDK_printf("Spheric XYZ\n");
		break;
	}

	//
	// Use the Rotation space only for the limits
	// (keep using eEulerXYZ for the rest)
	//
	FBXSDK_printf("        Use the Rotation Space for Limit specification only: %s\n",
		pNode->GetUseRotationSpaceForLimitOnly(FbxNode::eSourcePivot) ? "Yes" : "No");


	//
	// Inherit Type
	//
	FbxTransform::EInheritType lInheritType;
	pNode->GetTransformationInheritType(lInheritType);

	FBXSDK_printf("        Transformation Inheritance: ");

	switch (lInheritType)
	{
	case FbxTransform::eInheritRrSs:
		FBXSDK_printf("RrSs\n");
		break;
	case FbxTransform::eInheritRSrs:
		FBXSDK_printf("RSrs\n");
		break;
	case FbxTransform::eInheritRrs:
		FBXSDK_printf("Rrs\n");
		break;
	}
}

void FBXLoad::FbxLoader::DisplayGeometricTransform(FbxNode* pNode)
{
	FbxVector4 lTmpVector;

	FBXSDK_printf("    Geometric Transformations\n");

	//
	// Translation
	//
	lTmpVector = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FBXSDK_printf("        Translation: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

	//
	// Rotation
	//
	lTmpVector = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FBXSDK_printf("        Rotation:    %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

	//
	// Scaling
	//
	lTmpVector = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	FBXSDK_printf("        Scaling:     %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);
}

void FBXLoad::FbxLoader::DisplayMetaData(FbxScene* pScene)
{
	FbxDocumentInfo* sceneInfo = pScene->GetSceneInfo();
	if (sceneInfo)
	{
		FBXSDK_printf("\n\n--------------------\nMeta-Data\n--------------------\n\n");
		FBXSDK_printf("    Title: %s\n", sceneInfo->mTitle.Buffer());
		FBXSDK_printf("    Subject: %s\n", sceneInfo->mSubject.Buffer());
		FBXSDK_printf("    Author: %s\n", sceneInfo->mAuthor.Buffer());
		FBXSDK_printf("    Keywords: %s\n", sceneInfo->mKeywords.Buffer());
		FBXSDK_printf("    Revision: %s\n", sceneInfo->mRevision.Buffer());
		FBXSDK_printf("    Comment: %s\n", sceneInfo->mComment.Buffer());

		FbxThumbnail* thumbnail = sceneInfo->GetSceneThumbnail();
		if (thumbnail)
		{
			FBXSDK_printf("    Thumbnail:\n");

			switch (thumbnail->GetDataFormat())
			{
			case FbxThumbnail::eRGB_24:
				FBXSDK_printf("        Format: RGB\n");
				break;
			case FbxThumbnail::eRGBA_32:
				FBXSDK_printf("        Format: RGBA\n");
				break;
			}

			switch (thumbnail->GetSize())
			{
			default:
				break;
			case FbxThumbnail::eNotSet:
				FBXSDK_printf("        Size: no dimensions specified (%ld bytes)\n", thumbnail->GetSizeInBytes());
				break;
			case FbxThumbnail::e64x64:
				FBXSDK_printf("        Size: 64 x 64 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
				break;
			case FbxThumbnail::e128x128:
				FBXSDK_printf("        Size: 128 x 128 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
			}
		}
	}
}
