#include "ToolModulepch.h"
#include "EntityEditor.h"
#include "../EntityComponentSystem/ComponentHeader.h"
#include "../EntityComponentSystem/Serializer.h"


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

	LoadEntity(world);

	ImGui::Separator();

	for (Fire::ECS::Entity* ent : world->All(true))
	{
		//ImGui::Text()
		size_t id = ent->GetId();
		std::string idText = "ID:" + std::to_string(id);

		bool isSelected = (selectEnt == ent);

		if (isSelected)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));
		}

		if (ImGui::Button(idText.c_str()))
		{
			selectEnt = ent;
		}

		if (isSelected)
		{
			ImGui::PopStyleColor();
		}

		ImGui::SameLine();

		std::string destroyButton = "Destroy##" + std::to_string(id);
		if( ImGui::Button(destroyButton.c_str()))
		{
			world->Destroy(ent, false);
		}

		ImGui::Separator();
	}

	ImGui::End();

	// 삭제예정이면 nullptr
	if (selectEnt && selectEnt->IsPedingDestroy())
		selectEnt = nullptr;
}

void ToolModule::EntityEditor::LoadEntity(Fire::ECS::World* world)
{
	
	ImGui::InputText("Path", &loadPath);

	ImGui::SameLine();

	if (ImGui::Button("Load"))
	{
		std::filesystem::path filePath(loadPath);
		
		// 유효한 경로이다.

		if(std::filesystem::exists(filePath) && filePath.extension() == ".txt")
		{ 
			Fire::ECS::Entity* ent = world->Create();
			Fire::File::LoadEntity(ent, filePath.c_str());
		}
		else // 유효한 경로가 아니다
		{
			int a = 0;

		}
	}



}
