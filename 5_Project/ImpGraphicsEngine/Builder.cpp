#include "pch.h"
#include "Builder.h"

#include "ResourceManager.h"

#include "MeshObject.h"
#include "Resource.h"
using namespace ImpGraphics;

ImpGraphics::MeshObject* ImpGraphics::Builder::CreateMeshObject(std::wstring meshPath, std::wstring vertexShaderPath, std::wstring pixelShaderPath)
{
	std::shared_ptr<VBIB> vbib = _resourceManager->GetResource<VBIB>(meshPath);
	std::shared_ptr<Shader> shader = _resourceManager->GetResource<Shader>(vertexShaderPath, pixelShaderPath);

	MeshObject* meshObject = new MeshObject(vbib, shader);

	return meshObject;
}

ImpGraphics::MeshObject* Builder::CreateMeshObject(std::wstring meshPath, std::wstring vertexShaderPath, std::wstring pixelShaderPath, std::wstring vertexShaderPath2, std::wstring pixelShaderPath2)
{
	std::shared_ptr<VBIB> vbib = _resourceManager->GetResource<VBIB>(meshPath);
	std::shared_ptr<Shader> shader = _resourceManager->GetResource<Shader>(vertexShaderPath, pixelShaderPath);
	std::shared_ptr<Shader> shader2 = _resourceManager->GetResource<Shader>(vertexShaderPath2, pixelShaderPath2);

	MeshObject* meshObject = new MeshObject(vbib, shader, shader2);

	return meshObject;
}
