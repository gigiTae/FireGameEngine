#include "ToolModulepch.h"
#include "ComponentEditor.h"
#include "../Reflection/ReflectionHeader.h"


void ToolModule::ComponentEditor::Show(Fire::ECS::Entity* ent)
{
	ImGui::Begin("Component");
	if (ent != nullptr) 
	{
		std::string entInfo = "ID " + std::to_string(ent->GetId());
		ImGui::Text(entInfo.c_str());

		auto& components = ent->GetComponents();

		Fire::Reflect::TypeMap* typeMap = Fire::Reflect::TypeMap::GetTypeMap();

		for (auto& iter : components)
		{
			auto typeIndex = iter.first;

		 	Fire::Reflect::ITypeDescriptor* desc = typeMap->GetTypeDescriptor(typeIndex);
			
		}


	}
	ImGui::End();
}
