#include "Serializer.h"
#include "ReflectionHeader.h"
#include <fstream>

void Fire::File::LoadEntity(Fire::ECS::Entity* ent, const std::filesystem::path& path)
{
	assert(ent != nullptr && "Save�� �Ұ����մϴ�.");

	std::string line;
	std::ifstream readData(path);
	if (readData.is_open())
	{
		std::getline(readData, line);

		if (line != "Entity Serialize ID:1")
			assert("�߸��� �����͸� �о����ϴ�");

		std::string fileContent((std::istreambuf_iterator<char>(readData)),
			std::istreambuf_iterator<char>());
	
		size_t nowRead = 0;
		size_t open = 0;
		size_t close = 0;

		line = StringHelper::GetTypeName(fileContent, nowRead);
		do 
		{

			TypeIndex index = Fire::Reflect::TypeMap::GetTypeMap()->GetTypeIndex(line);
			assert(index.name() != "int");

			Fire::ECS::IComponentContainer* container = ent->Assign(index);

			Fire::Reflect::TypeDescriptor*  desc = 
				Fire::Reflect::TypeMap::GetTypeMap()->GetTypeDescriptor(line);

			open = StringHelper::FindOpeningBrace(fileContent, nowRead);
			close = StringHelper::FindClosingBrace(fileContent, nowRead);
			nowRead = close + 1;

			desc->Read(container->GetAddress(), fileContent, open, close);

			line = StringHelper::GetTypeName(fileContent, nowRead);

		} while (!line.empty());

	}


	

}

void Fire::File::SaveEntity(Fire::ECS::Entity* ent, const std::filesystem::path& path)
{
	assert(ent != nullptr && "Save�� �Ұ����մϴ�.");

	Fire::Reflect::TypeMap* typeMap = Fire::Reflect::TypeMap::GetTypeMap();

	std::string output = "Entity Serialize ID:";
	output +=  std::to_string(ent->GetId());
	output += "\n";

	for (auto& iter : ent->GetComponents())
	{
		Fire::Reflect::TypeDescriptor* desc = typeMap->GetTypeDescriptor(iter.first);

		Fire::ECS::IComponentContainer* container = iter.second;

		desc->Write(container->GetAddress(), output);
		output += "\n";
	}

	std::ofstream out(path);

	if (out.is_open())
	{
		out << output;
		out.close();
	}


	return;
}
