#pragma once
#include "BuildInfo.h"

namespace ImpGraphics
{
	class IObject;
	class MeshObject;
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
					return CreateMeshObject(args...);
				case ImpGraphics::ObjectType::HelperObject:
					return nullptr;
				default:
					return nullptr;
			}
			return nullptr;
		}

		MeshObject* CreateMeshObject(std::wstring meshPath, std::wstring vertexShaderPath, std::wstring pixelShaderPath);
		MeshObject* CreateMeshObject(std::wstring meshPath, std::wstring vertexShaderPath, std::wstring pixelShaderPath, 
			std::wstring vertexShaderPath2, std::wstring pixelShaderPath2);

	private:
		ResourceManager* _resourceManager;
	};
}