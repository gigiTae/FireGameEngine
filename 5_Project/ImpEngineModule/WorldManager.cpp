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
	/// Entity���ҽ��� �޾ƿ´�.
	EntityResource* entRes = _resourceManager->GetEntityResource(path);

	assert(entRes && "��ȿ���� �ʴ� ���ҽ��Դϴ�.");

	/// �̸������ص� Entity�� �����͸� �����Ѵ�.
	entRes->Clone(ent);
}

void ImpEngineModule::WorldManager::LoadEntity(const std::filesystem::path& path, Entity* ent) const
{
	/// Entity�� �̸��� ���ϸ� 
	std::string name = path.filename().string();
	ImpStringHelper::RemoveSubstring(name, ".ent");

	ent->SetName(name);

	std::ifstream readData(path);

	/// ���÷����� ����ؼ� Entity�� �ε��Ѵ�.
	ImpReflection::TypeManager* typeMgr = ImpReflection::TypeManager::GetInstance();

	if (readData.is_open())
	{
		std::string fileContent((std::istreambuf_iterator<char>(readData)),
			std::istreambuf_iterator<char>());

		size_t nowRead = 0, open = 0, close = 0;

		// ù��°���� Entity�� �������̴�.
		nowRead = fileContent.find('\n') + 1;

		std::string typeName = ImpStringHelper::GetTypeName(fileContent, nowRead);

		if (typeName.empty())
		{
			// ���� Entity�� ���
			return;
		}
		// ���÷����� �̿��ؼ� Entity ������ �ҷ��´�.
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

			// Component }\nComponentName �̹Ƿ� +2
			nowRead = close + 2;
			typeName = ImpStringHelper::GetTypeName(fileContent, nowRead);

		} while (!typeName.empty());
	}
	else
	{
		assert(!"�����б⿡ �����Ͽ����ϴ�.");
	}


}

void ImpEngineModule::WorldManager::LoadWorld()
{
	// 0. ������ ��θ� ���´�.
	std::filesystem::path worldPath = PathManager::GetWorldPath(_currentWorld);

	// 1.���ҽ� �Ŵ����� ���ؼ� LoadEntityList�� �޸� �߰��Ѵ�.
	std::filesystem::path loadEntityListPath = worldPath;
	loadEntityListPath += "/LoadEntityList.txt";
	_resourceManager->LoadEntityList(loadEntityListPath);

	// 2. StartEntity���� World�� �߰��Ѵ�.
	auto startEntityList = PathManager::GetStartEntityList(worldPath);

	// 3. Entity���� �����Ѵ�.
	for (auto& entPath : startEntityList)
	{
		LoadEntity(entPath, _world->CreateEntity());
	}

	// 4.������ Entity���� ���������� �����Ѵ�.

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

	assert(ent != nullptr && "��ƼƼ �̸� �б� ����");

	std::ifstream readData(path);

	if (readData.is_open())
	{
		std::string info;
		std::getline(readData, info);

		// ���� �̸��� Parent< �ΰ�찡 ������?
		size_t start = info.find("Parent<");
		size_t end = info.find_last_of(">");

		// �θ� ���� ��� 
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
	// 1. ���� ���带 �ʱ�ȭ�ϰ� �ʿ���� ���ҵ��� �޸𸮿��� �����Ѵ�.
	_world->Reset();
	_resourceManager->UnloadAllEntityResources();

	// 2. ���� ���忡�� �ʿ��� ���ҽ����� �ε��Ѵ�.
	_currentWorld = worldName;
	LoadWorld();

	// 3. ���带 �����Ѵ�.
	_world->Start();
}

