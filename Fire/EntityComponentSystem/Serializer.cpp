#include "Serializer.h"
#include "ReflectionHeader.h"
#include <fstream>

void Fire::File::LoadEntity(Fire::ECS::Entity* ent, const std::filesystem::path& path)
{
	assert(ent != nullptr && "Save�� �Ұ����մϴ�.");



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
