#include "ImpToolModulePCH.h"
#include "ImpEditor.h"
#include "WorldViewer.h"
#include "ComponentViewer.h"
#include "EntityViewer.h"
#include "ResourceViewer.h"
#include "ToolCamera.h"

ImpToolModule::ImpEditor::ImpEditor()
	:_engineModule(nullptr)
{
	_worldViewer = std::make_unique<WorldViewer>();
	_entityViewer = std::make_unique<EntityViewer>();
	_componentViewer = std::make_unique<ComponentViewer>();
	_resourceViewer = std::make_unique<ResourceViewer>();
}

ImpToolModule::ImpEditor::~ImpEditor()
{}

void ImpToolModule::ImpEditor::Initialize(HWND hWnd, void* device, void* deviceContext, ImpEngineModule::EngineModule* engineModule)
{
	// ImGui √ ±‚»≠
	InitializeImGui(hWnd, reinterpret_cast<ID3D11Device*>(device),
		reinterpret_cast<ID3D11DeviceContext*>(deviceContext));

	_engineModule = engineModule;
	
	_worldViewer->Initialize(_engineModule);
	_entityViewer->Initialize(_engineModule);
	_resourceViewer->Initalize();

	// ToolCamera
	_toolCamera = std::make_unique<ToolCamera>();
	_toolCamera->Initialize(_engineModule);
}

void ImpToolModule::ImpEditor::Finalize()
{
	FinalizeImGui();

	_toolCamera->Finalize();
}

void ImpToolModule::ImpEditor::Update()
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	
	static bool f = true;
	ImGui::ShowDemoWindow(&f);

	_worldViewer->Update();
	_resourceViewer->Update();
	_entityViewer->Update();
	_componentViewer->Update(_entityViewer->GetSelectEntity());

	_toolCamera->Update();
}

void ImpToolModule::ImpEditor::NewFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImpToolModule::ImpEditor::EndRender()
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

ImpEngineModule::Entity* ImpToolModule::ImpEditor::GetToolCamera() const
{
	return _toolCamera->GetEntity();
}

void ImpToolModule::ImpEditor::InitializeImGui(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 18.f, NULL, io.Fonts->GetGlyphRangesKorean());

	ImGuiStyle& style = ImGui::GetStyle();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(device, deviceContext);
}

void ImpToolModule::ImpEditor::FinalizeImGui()
{
	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

