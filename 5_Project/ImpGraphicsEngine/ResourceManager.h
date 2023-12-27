#pragma once
#include <memory>
#include "Resource.h"

// ���丮
// ����
// ���ҽ� �Ŵ���
// �δ�

// T CreateObject(BuildInfo* info);
// IObjectBase* _newObject = CreateObject<MeshObject*>(buildInfo);
// �ϴ� å�� �а� �� ��ü�� �ؾ� �ϴ� ���� ������ ���� ���غ���

namespace ImpGraphics
{
	class ImpDevice;

	class ResourceManager 
	{
	public:
		ResourceManager(ImpDevice* device);
		~ResourceManager();

		//std::shared_ptr<Resource> GetResource(const std::string& key);

		// ����� ���̴� ���ؽ�, �ȼ�
		// ���ؽ� ����, �ε��� ����

		template<typename ResourceType>
		std::shared_ptr<ResourceType> GetResource(const std::wstring& path)
		{
			std::shared_ptr<Resource> resource = _resources[path].lock();
			std::shared_ptr<ResourceType> resourceTypePtr;
			if (!resource)
			{
				_resources[path] = resource = std::make_shared<ResourceType>(this);
				resourceTypePtr = std::dynamic_pointer_cast<ResourceType>(resource);
				resourceTypePtr->Load(path);
			}
			else
			{
				resourceTypePtr = std::dynamic_pointer_cast<ResourceType>(resource);
			}

			return resourceTypePtr;
		}

		template<typename ResourceType, typename ...Types>
		std::shared_ptr<ResourceType> GetResource(const std::wstring& path, Types... args)
		{
			// sizeof...(args)
			std::shared_ptr<Resource> resource = _resources[path].lock();
			std::shared_ptr<ResourceType> resourceTypePtr;
			if (!resource)
			{
				_resources[path] = resource = std::make_shared<ResourceType>(this);
				resourceTypePtr = std::dynamic_pointer_cast<ResourceType>(resource);
				resourceTypePtr->Load(path, args...);
			}
			else
			{
				resourceTypePtr = std::dynamic_pointer_cast<ResourceType>(resource);
			}

			return resourceTypePtr;
		}

		ImpDevice* GetDevice() { return _device; }
	private:
		std::unordered_map<std::wstring, std::weak_ptr<Resource>> _resources;
		// FBX �δ�
		ImpDevice* _device;
	};
}