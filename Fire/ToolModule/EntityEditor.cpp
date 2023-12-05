#include "ToolModulepch.h"
#include "EntityEditor.h"

void ToolModule::EntityEditor::Show(Fire::ECS::World* world)
{
	ImGui::Begin("Entity");

	///

	if (ImGui::Button("Create Entity"))
	{
		// Entity ¸¸µé±â 
		world->Create();
	}

	for (Fire::ECS::Entity* ent : world->All(false))
	{
		//ImGui::Text()
		size_t id = ent->GetId();
		std::string idText = "ID : " + std::to_string(id);
	
		if(ImGui::Button(idText.c_str()))
		{
			selectEnt = ent;
		}

	}

	ImGui::End();
}
