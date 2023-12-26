#include "ImpToolModulePCH.h"
#include "ResourceViewer.h"

ImpToolModule::ResourceViewer::ResourceViewer()
{

}

ImpToolModule::ResourceViewer::~ResourceViewer()
{

}

void ImpToolModule::ResourceViewer::Initalize()
{
	_resourcesPath = ImpEngineModule::PathManager::GetResourcesPath();
	_currentPath = ImpEngineModule::PathManager::GetResourcesPath();
}

void ImpToolModule::ResourceViewer::Update()
{
	using namespace ImpEngineModule;


	if (ImGui::Begin("ResourceViewer"))
	{
		if (ImGui::BeginTabBar("ResourceTapBar")) {
			// ù ��° �� ����
			if (ImGui::BeginTabItem("Project"))
			{
				ProjectTabBar();
				ImGui::EndTabItem();
			}

			// �� ��° �� ����
			if (ImGui::BeginTabItem("Example"))
			{
				ImGui::EndTabItem();
			}

			// �� �� ����
			ImGui::EndTabBar();
		}


		ImGui::End();
	}

}

void ImpToolModule::ResourceViewer::ProjectTabBar()
{
	using namespace ImpEngineModule;

	auto dataList = PathManager::GetDirectoryList(_currentPath);

	if (_currentPath != _resourcesPath)
	{
		if (ImGui::Button("..."))
		{
			_currentPath = _currentPath.parent_path();
		}
	}

	// ���� ���� ���� 
	for (auto& path : dataList)
	{
		if (std::filesystem::is_directory(path))
		{
			std::string directory = path.filename().string();
			if (ImGui::Button(directory.c_str()))
			{
				_currentPath = path;
			}
		}
	}

	// Entity
	for (auto& path : dataList)
	{
		if (!std::filesystem::is_directory(path))
		{
			std::string entName = path.filename().string();
			ImGui::Text(entName.c_str());
			std::wstring entPath = path.wstring();
			
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				ImGui::Text(entName.c_str());
				ImGui::SetDragDropPayload("EntityPath", entPath.c_str(), (entPath.size() + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}
		}
	}
}
