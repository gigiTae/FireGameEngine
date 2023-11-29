#include "StringConverter.h"
#include "World.h"
#include "EntityView.h"

Fire::ECS::StringConverter::StringConverter()
{
}

Fire::ECS::StringConverter::~StringConverter()
{
}

void Fire::ECS::StringConverter::SerializeWorld(World* world, const std::wstring& path, const std::wstring& name)
{
	std::ofstream outputFile(GetFilePath(path, name), std::ios::out);

	if (!outputFile.is_open())
	{
		//TODO : log or assert
		return;
	}

	for (Entity* ent : world->All())
	{
		SerializeEntity(ent,outputFile);
	}

	outputFile.close();
}

void Fire::ECS::StringConverter::SerializeEntity(Entity* ent, std::ofstream& outputFile)
{
	for (auto& iter : ent->GetComponents())
	{
		iter.second;
	}

}

void Fire::ECS::StringConverter::DeserializeWorld(World* world, const std::wstring& path)
{
}

void Fire::ECS::StringConverter::DeserializeEntity(Entity* ent)
{
}

std::wstring Fire::ECS::StringConverter::GetFilePath(const std::wstring& path, const std::wstring& name)
{
	return path + L"\\" + name + fileFomat;
}