#include "pch.h"
#include "Builder.h"

#include "ResourceManager.h"

#include "MeshObject.h"
#include "Resource.h"
using namespace ImpGraphics;

ImpGraphics::MeshObject* ImpGraphics::Builder::CreateMeshObject(std::wstring meshPath, std::wstring shaderPath)
{
	std::shared_ptr<VBIB> vbib = _resourceManager->GetResource<VBIB>(meshPath);
	std::shared_ptr<Shader> shader = _resourceManager->GetResource<Shader>(shaderPath);

	MeshObject* meshObject = new MeshObject(vbib, shader);

	return meshObject;
}