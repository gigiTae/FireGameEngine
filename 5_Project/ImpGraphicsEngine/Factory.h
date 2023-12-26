#pragma once
#include "IImp3DRenderer.h"
#include "Builder.h"

#include "BuildInfo.h"

// T CreateObject(BuildInfo* info);
// IObjectBase* _newObject = CreateObject<MeshObject*>(buildInfo);

namespace ImpGraphics
{
	class ObjectManager;
	class ResourceManager;

	class Factory
	{
	public:
		Factory(ResourceManager* resourceManager);
		~Factory();

		template <typename ...types>
		IObject* CreateObject(ObjectType objectType, types... args)
		{
			return _builder->Create(objectType, args...);
		}

	private:
		Builder* _builder;

		ObjectManager* _objectManager;
		ResourceManager* _resourceManager;
	};
}