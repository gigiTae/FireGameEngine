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
	_entityPath = ImpEngineModule::PathManager::GetEntityDataPath();

}

void ImpToolModule::ResourceViewer::Update()
{
	using namespace ImpEngineModule;


	if (ImGui::Begin("ResourceViewer"))
	{
		if (ImGui::BeginTabBar("ResourceTapBar")) {
			// ù ��° �� ����
			if (ImGui::BeginTabItem("Entity"))
			{
				EntityTabBar();
				ImGui::EndTabItem();
			}

			// �� ��° �� ����
			if (ImGui::BeginTabItem("FBX"))
			{
				ImGui::EndTabItem();
			}

			// �� ��° �� ����
			if (ImGui::BeginTabItem("Sound"))
			{
				ImGui::EndTabItem();
			}

			// �� �� ����
			ImGui::EndTabBar();
		}


		ImGui::End();
	}

}

void ImpToolModule::ResourceViewer::EntityTabBar()
{
	using namespace ImpEngineModule;

	auto dataList = PathManager::GetDirectoryList(_entityPath);

	if (_entityPath != PathManager::GetEntityDataPath())
	{
		if (ImGui::Button("Prev"))
		{
			_entityPath = _entityPath.parent_path();
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
				_entityPath = path;
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
