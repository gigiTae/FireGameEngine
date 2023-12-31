#include "EngineModulePCH.h"
#include "WorldManager.h"
#include "World.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "EntityResource.h"
#include "Transform.h"

ImpEngineModule::WorldManager::WorldManager()
	: _world(nullptr), _typeManager(nullptr), _currentWorld{},
	_resourceManager(nullptr)
{

}

ImpEngineModule::WorldManager::~WorldManager()
{

}

void ImpEngineModule::WorldManager::Initialize(const std::wstring& startWorld, ImpEngineModule::World* world, ImpEngineModule::ResourceManager* resMgr)
{
	_currentWorld = startWorld;
	_typeManager = ImpReflection::TypeManager::GetInstance();
	_world = world;
	_resourceManager = resMgr;
}

void ImpEngineModule::WorldManager::Finalize()
{

}

void ImpEngineModule::WorldManager::LoadToEntityResource(const std::filesystem::path& path, ImpEngineModule::Entity* ent)
{
	/// Entity리소스를 받아온다.
	EntityResource* entRes = _resourceManager->GetEntityResource(path);

	assert(entRes && "유효하지 않는 리소스입니다.");

	/// 미리생성해둔 Entity에 데이터를 복사한다.
	entRes->Clone(ent);
}

void ImpEngineModule::WorldManager::LoadEntity(const std::filesystem::path& path, Entity* ent) const
{
	/// Entity의 이름은 파일명 
	std::string name = path.filename().string();
	ImpStringHelper::RemoveSubstring(name, ".ent");

	ent->SetName(name);

	std::ifstream readData(path);

	/// 리플렉션을 사용해서 Entity를 로드한다.
	ImpReflection::TypeManager* typeMgr = ImpReflection::TypeManager::GetInstance();

	if (readData.is_open())
	{
		std::string fileContent((std::istreambuf_iterator<char>(readData)),
			std::istreambuf_iterator<char>());

		size_t nowRead = 0, open = 0, close = 0;

		// 첫번째줄은 Entity의 데이터이다.
		nowRead = fileContent.find('\n') + 1;

		std::string typeName = ImpStringHelper::GetTypeName(fileContent, nowRead);

		if (typeName.empty())
		{
			// 깡통 Entity의 경우
			return;
		}
		// 리플렉션을 이용해서 Entity 정보를 불러온다.
		do
		{
			TypeIndex index = typeMgr->GetTypeIndex(typeName);

			assert(index != ImpEngineModule::EXCEPTION);

			ImpReflection::Type* type = typeMgr->GetType(index);

			open = ImpStringHelper::FindOpeningBrace(fileContent, nowRead);
			close = ImpStringHelper::FindClosingBrace(fileContent, nowRead);

			std::string sub = fileContent.substr(open, close - open - 1);

			void* component = type->Invoke(fileContent, open, close);

			ent->AddComponent(component, index);

			// Component }\nComponentName 이므로 +2
			nowRead = close + 2;
			typeName = ImpStringHelper::GetTypeName(fileContent, nowRead);

		} while (!typeName.empty());
	}
	else
	{
		assert(!"파일읽기에 실패하였습니다.");
	}


}

void ImpEngineModule::WorldManager::LoadWorld()
{
	// 0. 월드의 경로를 얻어온다.
	std::filesystem::path worldPath = PathManager::GetWorldPath(_currentWorld);

	// 1.리소스 매니져를 통해서 LoadEntityList를 메모리 추가한다.
	std::filesystem::path loadEntityListPath = worldPath;
	loadEntityListPath += "/LoadEntityList.txt";
	_resourceManager->LoadEntityList(loadEntityListPath);

	// 2. StartEntity들을 World에 추가한다.
	auto startEntityList = PathManager::GetStartEntityList(worldPath);

	// 3. Entity들을 생성한다.
	for (auto& entPath : startEntityList)
	{
		LoadEntity(entPath, _world->CreateEntity());
	}

	// 4.생성한 Entity들을 계층구조로 연결한다.
	for (auto& entPath : startEntityList)
	{
		BuildEntityHierachy(entPath);
	}


}

void ImpEngineModule::WorldManager::BuildEntityHierachy(const std::filesystem::path& path)
{
	std::string name = path.filename().string();
	ImpStringHelper::RemoveSubstring(name, ".ent");

	Entity* ent = _world->GetEntity(name);

	assert(ent != nullptr && "엔티티 이름 읽기 실패");

	std::ifstream readData(path);

	if (readData.is_open())
	{
		std::string info;
		std::getline(readData, info);

		// 설마 이름이 Parent< 인경우가 있을까?
		size_t start = info.find("Parent<");
		size_t end = info.find_last_of(">");

		// 부모가 없는 경우 
		if (start == std::string::npos)
		{
			readData.close();
			return;
		}

		start = start + std::string("Parent<").length();

		std::string parentName = info.substr(start, end - start);

		Entity* parent = _world->GetEntity(parentName);

		assert(parent != nullptr);

		ent->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());

		readData.close();
	}
}

void ImpEngineModule::WorldManager::ChangeWorld(const std::wstring& worldName)
{
	// 1. 현재 월드를 초기화하고 필요없는 리소들을 메모리에서 해제한다.
	_world->Reset();
	_resourceManager->UnloadAllEntityResources();

	// 2. 다음 월드에서 필요한 리소스들을 로드한다.
	_currentWorld = worldName;
	LoadWorld();

	// 3. 월드를 시작한다.
	_world->Start();
}

