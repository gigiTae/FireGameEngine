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
	/// Entity Prefab을 가지고 있는다. 
	const std::wstring& path = GetPath();
	
	_entity = std::make_unique<Entity>();

	/// Entity의 이름은 파일명
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

			_entity->AddComponent(component, index);

			// Component }\nComponentName 이므로 +2
			nowRead = close + 2;
			typeName = ImpStringHelper::GetTypeName(fileContent, nowRead);

		} while (!typeName.empty());
	}
	else
	{
		std::wstring path = GetPath();

		assert(!"파일읽기에 실패하였습니다.");
	}

}

void ImpEngineModule::EntityResource::Clone(Entity* ent) const
{
	// 이동생성자 
	(*ent) = (*_entity);
}


