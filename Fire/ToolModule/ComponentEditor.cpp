#include "ToolModulepch.h"
#include "ComponentEditor.h"



void ToolModule::ComponentEditor::Show(Fire::ECS::Entity* ent)
{
	ImGui::Begin("Component");
	if (ent != nullptr) 
	{
		std::string entInfo = "id :" + std::to_string(ent->GetId());

		ImGui::Text(entInfo.c_str());

	}
	ImGui::End();
}
