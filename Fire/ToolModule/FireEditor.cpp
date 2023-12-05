#include "ToolModulepch.h"
#include "FireEditor.h"

ToolModule::FireEditor::FireEditor()
{}

ToolModule::FireEditor::~FireEditor()
{}

void ToolModule::FireEditor::Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, deviceContext);
}

void ToolModule::FireEditor::Finalize()
{
		// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ToolModule::FireEditor::NewFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ToolModule::FireEditor::EndRender()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();

	// Update and Render additional Platform Windows
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void ToolModule::FireEditor::Load(Fire::ECS::World* world)
{
	/// Sysytem 
	StartSystemEditor(world);

	/// Entity 
	StartEntityEditor(world);

	/// Component
	StartComponentEditor(world);
}

void ToolModule::FireEditor::StartEntityEditor(Fire::ECS::World* world)
{
	entityEditor.Show(world);
}

void ToolModule::FireEditor::StartComponentEditor(Fire::ECS::World* world)
{
	compentEditor.Show(entityEditor.GetSelectEntity());
}

void ToolModule::FireEditor::StartSystemEditor(Fire::ECS::World* world)
{
	systemEditor.Show(world);
}

