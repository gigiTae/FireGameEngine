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

		// ������ �׷��Ƚ� ������ ���ε��� ��� ���ε��� �����Ѵ�.
		if (mesh->IsBindGraphics())
		{
			mesh->SetBindGraphics(false);
			graphicsEngine->DeleteMeshObject(ent->GetID());
		}

		// ������Ʈ ��Ȱ��ȭ�̹Ƿ� ���ε� ����
		if (!mesh->IsActive())
		{
			return;
		}

		MeshObjectInfo meshInfo;

		meshInfo._objectID = ent->GetID();
		meshInfo._meshPath = mesh->GetFBXPath();
		meshInfo._pisxelShaderPath = mesh->GetPixelShaderPath();
		meshInfo._vertexShaderPath= mesh->GetVertexShaderPath();

		// ���ε��� ������ Ȯ���Ѵ�
	
		// 1. ��ΰ� ���� ��� ���ε����� �ʴ´�.
		if (meshInfo._meshPath.empty() || meshInfo._pisxelShaderPath.empty()
			|| meshInfo._vertexShaderPath.empty())
		{
			return;
		}

		// 2. Ȯ���ڸ��� Ȯ���ϰ� ���� ������ �ʱ�ȭ�Ѵ�.

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


		// 3. �׷��Ƚ������� ���ε��Ѵ�.
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
