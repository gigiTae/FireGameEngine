#include "ImpToolModulePCH.h"
#include "Rebind.h"
#include "../ImpGraphicsEngine/ImpGraphicsEngine.h"


void ImpToolModule::Bind::RebindMeshObject(ImpEngineModule::Entity* ent, ImpGraphics::IImpGraphicsEngine* graphicsEngine)
{
	using namespace ImpEngineModule;
	using namespace ImpGraphics;

	if (ent->HasComponent<Mesh>())
	{
		Mesh* mesh = ent->GetComponent<Mesh>();

		// 이전에 그래픽스 엔진에 바인딩된 경우 바인딩을 해제한다.
		if (mesh->IsBindGraphics())
		{
			mesh->SetBindGraphics(false);
			graphicsEngine->DeleteMeshObject(ent->GetID());
		}

		// 컴포넌트 비활성화이므로 바인딩 해제
		if (!mesh->IsActive())
		{
			return;
		}

		MeshObjectInfo meshInfo;

		meshInfo._objectID = ent->GetID();
		meshInfo._meshPath = mesh->GetFBXPath();
		meshInfo._pisxelShaderPath = mesh->GetPixelShaderPath();
		meshInfo._vertexShaderPath= mesh->GetVertexShaderPath();

		// 바인딩할 정보를 확인한다
	
		// 1. 경로가 없는 경우 바인딩하지 않는다.
		if (meshInfo._meshPath.empty() || meshInfo._pisxelShaderPath.empty()
			|| meshInfo._vertexShaderPath.empty())
		{
			return;
		}

		// 2. 확장자명을 확인하고 맞지 않으면 초기화한다.

		// FBX
		std::wstring meshPathExtension = PathManager::GetExtension(meshInfo._meshPath);
		if (meshPathExtension != L".fbx")
		{
			mesh->SetFBXPath(std::wstring());
			return;
		}

		// hlsl , cso
		std::wstring pixelExtension = PathManager::GetExtension(meshInfo._pisxelShaderPath);
		if (!(pixelExtension == L".cso" || pixelExtension == L".hlsl"))
		{
			mesh->SetPixelShaderPath(std::wstring());
			return;
		}

		// hlsl , cso
		std::wstring vertexExtension = PathManager::GetExtension(meshInfo._vertexShaderPath);
		if (!(vertexExtension == L".cso" || vertexExtension == L".hlsl"))
		{
			mesh->SetVertexShaderPath(std::wstring());
			return;
		}


		// 3. 그래픽스엔진에 바인딩한다.
		graphicsEngine->AddMeshObejct(meshInfo);
		mesh->SetBindGraphics(true);
	}


}

void ImpToolModule::Bind::RebindLightObject(ImpEngineModule::Entity* eny, ImpGraphics::IImpGraphicsEngine* graphicsEngine)
{

}

void ImpToolModule::Bind::Rebind(ImpEngineModule::Entity* ent, ImpGraphics::IImpGraphicsEngine* graphicsEngine)
{
	if (ent == nullptr)
	{
		return;
	}

	RebindMeshObject(ent, graphicsEngine);

	RebindLightObject(ent, graphicsEngine);
}
