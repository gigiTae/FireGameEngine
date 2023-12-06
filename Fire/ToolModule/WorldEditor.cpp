#include "ToolModulepch.h"
#include "WorldEditor.h"

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
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

}

