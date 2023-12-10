#include "Serializer.h"
#include "ReflectionHeader.h"
#include <fstream>

void Fire::File::LoadEntity(Fire::ECS::Entity* ent, const std::filesystem::path& path)
{
	assert(ent != nullptr && "Save가 불가능합니다.");

	std::string line;
	std::ifstream readData(path);
	if (readData.is_open())
	{
		std::getline(readData, line);

		if (line != "Entity Serialize ID:1")
			assert("잘못된 데이터를 읽었습니다");

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
			
			///DEBUG
			std::string subData = fileContent.substr(nowRead, close - nowRead+1);
			///

			/// *** str[0] 부터 시작이므로 close +1 해야한다.
			desc->Read(container->GetAddress(), fileContent, nowRead, close);

			// Component }\nComponentName 이므로 +2
			nowRead = close + 2;
			line = StringHelper::GetTypeName(fileContent, nowRead);

		} while (!line.empty());

	}


	

}

void Fire::File::SaveEntity(Fire::ECS::Entity* ent, const std::filesystem::path& path)
{
	assert(ent != nullptr && "Save가 불가능합니다.");

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
