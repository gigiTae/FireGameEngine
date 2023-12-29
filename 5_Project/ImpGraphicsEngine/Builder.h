#pragma once
#include "BuildInfo.h"

#include "MeshObject.h"
#include "QuadObject.h"

#include "ResourceManager.h"
#include "Resource.h"

namespace ImpGraphics
{
	class IObject;
	class MeshObject;
	class QuadObject;

	class ResourceManager;

	class Builder
	{
	public:
		Builder(ResourceManager* resourceManager)
			: _resourceManager(resourceManager) {}
		~Builder() {};

		template <typename ...types>
		IObject* Create(ObjectType objectType, types... args)
		{
			switch (objectType)
			{
				case ImpGraphics::ObjectType::MeshObject:
					return CreateObject<MeshObject>(ImpGraphics::ObjectType::MeshObject, args...);
				case ImpGraphics::ObjectType::HelperObject:
					return nullptr;
				case ImpGraphics::ObjectType::QuadObject:
					return CreateObject<QuadObject>(ImpGraphics::ObjectType::QuadObject, args...);
				default:
					return nullptr;
			}
			return nullptr;
		}

// 		MeshObject* CreateMeshObject(std::wstring meshPath, std::wstring vertexShaderPath, std::wstring pixelShaderPath);
// 		QuadObject* CreateQuadObject(std::wstring meshPath, std::wstring vertexShaderPath, std::wstring pixelShaderPath);
		template<typename T>
		T* CreateObject(ImpGraphics::ObjectType ot, std::wstring meshPath, std::wstring vertexShaderPath, std::wstring pixelShaderPath);
	private:
		ResourceManager* _resourceManager;
	};

	template<typename T>
	T* ImpGraphics::Builder::CreateObject(ImpGraphics::ObjectType ot, std::wstring meshPath, std::wstring vertexShaderPath, std::wstring pixelShaderPath)
	{
		std::shared_ptr<VBIB> vbib = _resourceManager->GetResource<VBIB>(meshPath);
		std::shared_ptr<Shader> shader;
		if (ot == ObjectType::MeshObject)
		{
			shader = _resourceManager->GetResource<Shader>(vertexShaderPath, pixelShaderPath, 0);
		}
		else
		{
			shader = _resourceManager->GetResource<Shader>(vertexShaderPath, pixelShaderPath, 1);
		}

		T* meshObject = new T(vbib, shader);

		return meshObject;
	}
}