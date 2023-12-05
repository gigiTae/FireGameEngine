#include "ToolModulepch.h"
#include "SystemEditor.h"

ToolModule::SystemEditor::SystemEditor()
{
}

ToolModule::SystemEditor::~SystemEditor()
{

}

void ToolModule::SystemEditor::Show(Fire::ECS::World* world)
{
	ImGui::Begin("System");

	ImGui::End();
}
