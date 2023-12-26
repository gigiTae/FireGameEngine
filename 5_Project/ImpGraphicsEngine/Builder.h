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
					break;
				default:
					break;
			}
		}

		MeshObject* CreateMeshObject(std::wstring meshPath, std::wstring shaderPath);

	private:
		ResourceManager* _resourceManager;
	};
}