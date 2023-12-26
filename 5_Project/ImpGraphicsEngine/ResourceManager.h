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
			if (!resource)
			{
				_resources[path] = resource = std::make_shared<ResourceType>(this);
				resource->Load(path);
			}

			std::shared_ptr<ResourceType> return_value = std::dynamic_pointer_cast<ResourceType>(resource);
			return return_value;
		}

		ImpDevice* GetDevice() { return _device; }
	private:
		std::unordered_map<std::wstring, std::weak_ptr<Resource>> _resources;
		// FBX �δ�
		ImpDevice* _device;
	};
}