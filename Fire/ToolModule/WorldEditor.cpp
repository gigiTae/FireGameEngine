#include "ToolModulepch.h"
#include "WorldEditor.h"
#include "../EntityComponentSystem/Serializer.h"

ToolModule::WorldEditor::WorldEditor()
{

}

ToolModule::WorldEditor::~WorldEditor()
{

}

void ToolModule::WorldEditor::Show(Fire::ECS::World* world)
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Load"))
		{

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Save"))
		{
			if(ImGui::Button("EntitySave"))
			{
				std::filesystem::path filePath = std::filesystem::current_path().parent_path();
				filePath += "\\Resource\\World\\Entity.txt";

				Fire::File::SaveEntity(world->GetByIndex(0), filePath);	
				saveSucessfulPopup = true;
			}

			ImGui::EndMenu();
		}

		if (saveSucessfulPopup)
		{
			ImGui::OpenPopup("SaveSuccesful");
			saveSucessfulPopup = false;
		}

		if (ImGui::BeginPopupModal("SaveSuccesful", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Entity Save is Succesful");
			ImGui::Separator();

			if (ImGui::Button("OK", ImVec2(120, 0))) {
				ImGui::CloseCurrentPopup(); // ÆË¾÷ ´Ý±â
			}

			ImGui::EndPopup();
		}
		ImGui::EndMainMenuBar();
	}

}

