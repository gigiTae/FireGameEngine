#include "EngineModulePCH.h"
#include "ResourceManager.h"
#include "EntityResource.h"
#include "PathManager.h"

ImpEngineModule::ResourceManager::ResourceManager()
	:_entityData{}, _worldDataList{}
{

}

ImpEngineModule::ResourceManager::~ResourceManager()
{

}

void ImpEngineModule::ResourceManager::Initailize(const std::wstring startWorld)
{
	/// ����Data ������ ����� ��θ� ��ƿ´�.
	_worldDataList = PathManager::GetWorldDataList();
}

void ImpEngineModule::ResourceManager::Finalize()
{
	UnloadAllEntityResources();
}

ImpEngineModule::EntityResource* ImpEngineModule::ResourceManager::GetEntityResource(const std::wstring& path)
{
	auto iter = _entityData.find(path);

	if (iter == _entityData.end())
	{
		return nullptr;
	}

	return iter->second.get();
}

void ImpEngineModule::ResourceManager::LoadResource(const std::wstring& path)
{


}

void ImpEngineModule::ResourceManager::LoadEntityList(const std::wstring& path)
{
	// 1. txt ������ �д´�.
	std::wifstream entityList(path);

	if (entityList.is_open())
	{
		std::wstring line;
		std::wstring relativePath = PathManager::GetResourcesPath();

		while (std::getline(entityList, line))
		{
			// 2. EntityResource���� ����θ� ���ؼ� �ε��Ѵ�. 
			line = relativePath + line;

			LoadEntityResource(line);
		}

		entityList.close();
	}
	else
	{
		assert(!"���Ͽ��� ����");
	}

}

void ImpEngineModule::ResourceManager::LoadEntityResource(const std::wstring& path)
{
	EntityResource* entRes = new EntityResource(path);

	entRes->Load();

	// {} �߰�ȣ �ʱ�ȭ�� �Ұ����ϴ� 
	_entityData.insert(std::make_pair(path, entRes));
}

void ImpEngineModule::ResourceManager::UnloadAllEntityResources()
{
	_entityData.clear();

}
