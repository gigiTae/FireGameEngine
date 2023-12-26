#include "EngineModulePCH.h"
#include "EntityResource.h"
#include "Entity.h"

ImpEngineModule::EntityResource::EntityResource(const std::wstring& path)
	:Resource(ResourceCategory::Entity,path)
{}

ImpEngineModule::EntityResource::~EntityResource()
{

}

void ImpEngineModule::EntityResource::Load()
{
	/// Entity Prefab�� ������ �ִ´�. 
	const std::wstring& path = GetPath();
	
	_entity = std::make_unique<Entity>();

	/// Entity�� �̸��� ���ϸ�
	std::filesystem::path filePath(path);

	std::string name = filePath.filename().string();
	ImpStringHelper::RemoveSubstring(name, ".ent");
	
	_entity->SetName(name);

	LoadEntity();
}

ImpEngineModule::Entity* ImpEngineModule::EntityResource::Clone()
{
	Entity* ent = new Entity(*_entity);

	return ent;
}

void ImpEngineModule::EntityResource::LoadEntity()
{
	std::ifstream readData(GetPath());

	ImpReflection::TypeManager* typeMgr = ImpReflection::TypeManager::GetInstance();

	if (readData.is_open())
	{
		std::string fileContent((std::istreambuf_iterator<char>(readData)),
			std::istreambuf_iterator<char>());

		size_t nowRead = 0, open = 0, close = 0;

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

			_entity->AddComponent(component, index);

			// Component }\nComponentName �̹Ƿ� +2
			nowRead = close + 2;
			typeName = ImpStringHelper::GetTypeName(fileContent, nowRead);

		} while (!typeName.empty());
	}
	else
	{
		std::wstring path = GetPath();

		assert(!"�����б⿡ �����Ͽ����ϴ�.");
	}

}

void ImpEngineModule::EntityResource::Clone(Entity* ent) const
{
	// �̵������� 
	(*ent) = (*_entity);
}


