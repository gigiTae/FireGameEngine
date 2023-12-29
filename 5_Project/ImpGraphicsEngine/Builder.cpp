#include "pch.h"
#include "Builder.h"

#include "ResourceManager.h"
#include "Resource.h"

#include "MeshObject.h"
#include "QuadObject.h"

using namespace ImpGraphics;

/*
ImpGraphics::MeshObject* ImpGraphics::Builder::CreateMeshObject(std::wstring meshPath, std::wstring vertexShaderPath, std::wstring pixelShaderPath)
{
	std::shared_ptr<VBIB> vbib = _resourceManager->GetResource<VBIB>(meshPath);
	std::shared_ptr<Shader> shader = _resourceManager->GetResource<Shader>(vertexShaderPath, pixelShaderPath, 0);

	MeshObject* meshObject = new MeshObject(vbib, shader);

	return meshObject;
}*/