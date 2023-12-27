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
	/// 월드Data 내부의 월드들 경로를 담아온다.
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
	// 1. txt 파일을 읽는다.
	std::wifstream entityList(path);

	if (entityList.is_open())
	{
		std::wstring line;
		std::wstring relativePath = PathManager::GetResourcesPath();

		while (std::getline(entityList, line))
		{
			// 2. EntityResource들을 상대경로를 더해서 로드한다. 
			line = relativePath + line;

			LoadEntityResource(line);
		}

		entityList.close();
	}
	else
	{
		assert(!"파일오픈 실패");
	}

}

void ImpEngineModule::ResourceManager::LoadEntityResource(const std::wstring& path)
{
	EntityResource* entRes = new EntityResource(path);

	entRes->Load();

	// {} 중괄호 초기화는 불가능하다 
	_entityData.insert(std::make_pair(path, entRes));
}

void ImpEngineModule::ResourceManager::UnloadAllEntityResources()
{
	_entityData.clear();

}
