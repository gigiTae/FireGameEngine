#pragma once
#include "BuildInfo.h"

namespace ImpGraphics
{
	class IObject;
	class MeshObject;
	class ResourceManager;

	class IBuilder
	{
	public:
		IBuilder(ResourceManager* resourceManager)
			: _resourceManager(resourceManager) {}
		~IBuilder() {};

		template <typename ...types>
		IObject* Create(ObjectType objectType, types... args)
		{
			
		}

		MeshObject* CreateMeshObject(std::string meshPath, std::string shaderPath);

	protected:
		// 프로토타입 패턴 사용?
		std::unordered_map<ObjectType, IObject*> _prototypes;
		ResourceManager* _resourceManager;
	};
}