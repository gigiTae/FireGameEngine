#include "ToolModulepch.h"
#include "EntityEditor.h"
#include "../EntityComponentSystem/ComponentHeader.h"

ToolModule::EntityEditor::EntityEditor()
{
}

ToolModule::EntityEditor::~EntityEditor()
{
}

void ToolModule::EntityEditor::Show(Fire::ECS::World* world)
{
	ImGui::Begin("Entity");

	// Entity 만들기 
	if (ImGui::Button("Create Entity"))
	{
		Fire::ECS::Entity* ent = world->Create();
		ent->Assign<Fire::Component::Name>()->name = "component";
	}

	for (Fire::ECS::Entity* ent : world->All(true))
	{
		//ImGui::Text()
		size_t id = ent->GetId();
		std::string idText = "ID:" + std::to_string(id);

		if (ImGui::Button(idText.c_str()))
		{
			selectEnt = ent;
		}

		ImGui::SameLine();

		std::string destroyButton = "Destroy " + std::to_string(id);
		if( ImGui::Button(destroyButton.c_str()))
		{
			world->Destroy(ent, false);
		}

	}

	ImGui::End();

	// 삭제예정이면 nullptr
	if (selectEnt && selectEnt->IsPedingDestroy())
		selectEnt = nullptr;
}
