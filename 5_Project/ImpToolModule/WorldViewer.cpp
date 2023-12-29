#include "ImpToolModulePCH.h"
#include "WorldViewer.h"

ImpToolModule::WorldViewer::WorldViewer()
{

}

ImpToolModule::WorldViewer::~WorldViewer()
{

}

void ImpToolModule::WorldViewer::Initialize(ImpEngineModule::EngineModule* engineModule)
{
	_world = engineModule->GetWorld();
	_resourceManager = engineModule->GetResourceManager();
	_worldManager = engineModule->GetWorldManager();

	_currentWorldName = _worldManager->GetWorldName();

}


void ImpToolModule::WorldViewer::Update()
{
	_currentWorldName = _worldManager->GetWorldName();

	if (ImGui::BeginMainMenuBar())
	{
		CreateWorldButton();

		LoadWorldButton();

		SaveWorldButton();
		
		ShowWorldNameToText();

		ImGui::EndMainMenuBar();
	}
}

void ImpToolModule::WorldViewer::ShowWorldNameToText()
{
	std::string showText = "<";
	std::filesystem::path worldName(_currentWorldName);
	showText += worldName.string();
	showText += ">";

	float nameX = ImGui::GetWindowSize().x - ImGui::CalcTextSize(showText.c_str()).x;

	ImGui::SetCursorPosX(nameX);
	ImGui::PushStyleColor(ImGuiCol_Text, ImGuiColor::SPRING_GREEN);
	ImGui::Text(showText.c_str());
	ImGui::PopStyleColor();
}




void ImpToolModule::WorldViewer::SaveWorldButton()
{
	if (ImGui::BeginMenu("Save"))
	{
		if (ImGui::Button("SaveWorld"))
		{
			SaveWorld();
		}

		ImGui::EndMenu();
	}

	// ���̺꿡 �����ϸ� �˾�â ����
	if (_isSaveWorld)
	{
		ImGui::SetNextWindowSize(ImVec2(200.f, 50.f));
		ImGui::OpenPopup("Save Successed!!");

		if (ImGui::BeginPopupModal("Save Successed!!", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
				_isSaveWorld = false;
			}

			ImGui::EndPopup();
		}
	}

}

void ImpToolModule::WorldViewer::LoadWorldButton()
{
	using namespace ImpEngineModule;

	if (ImGui::BeginMenu("Load"))
	{
		auto worldList = PathManager::GetWorldDataList();

		for (auto& path : worldList)
		{
			std::string worldName = path.filename().string();

			if (ImGui::MenuItem(worldName.c_str()))
			{
				_worldManager->ChangeWorld(path.filename());
			}
		}


		ImGui::EndMenu();
	}
}

void ImpToolModule::WorldViewer::CreateWorldButton()
{

	if (ImGui::BeginMenu("Create"))
	{
		if (ImGui::MenuItem("CreateWorld"))
		{
			_isOpenCreatePopup = true;
		}

		ImGui::EndMenu();
	}

	if (_isOpenCreatePopup)
	{
		ImGui::OpenPopup("Enter World Name");

		if (ImGui::BeginPopupModal("Enter World Name", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{

			ImGui::InputText("World Name", &_inputWorldName);

			if (ImGui::Button("Create"))
			{
				// ���带 �����Ѵ�.
				ImGui::CloseCurrentPopup();
				_isOpenCreatePopup = false;
				CreateWorld();
			}

			ImGui::SameLine();

			// ccad
			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
				_isOpenCreatePopup = false;
			}

			ImGui::EndPopup();
		}
	}

}

void ImpToolModule::WorldViewer::CreateWorld()
{
	// 1. ���带 ������ �����Ѵ�.
	using namespace ImpEngineModule;
	namespace fs = std::filesystem;

	auto path = PathManager::GetWorldDataPath();
	path += "/";
	path += _inputWorldName;

	fs::create_directory(path);

	// LoadEntityList.txt ���ϻ���
	fs::path listPath = path;
	listPath += "/LoadEntityList.txt";
	std::wofstream  loadList(listPath);

	// StartEntity ���� ����
	path += "/StartEntity";
	fs::create_directory(path);

	_currentWorldName = fs::path(_inputWorldName);
	_worldManager->ChangeWorld(_currentWorldName);
}

void ImpToolModule::WorldViewer::SaveWorld()
{
	using namespace ImpEngineModule;
	namespace fs = std::filesystem;

	/// 1.���� ��θ� �����Ѵ�.
	fs::path  worldPath = PathManager::GetWorldDataPath();
	worldPath += "/";
	worldPath += _currentWorldName;

	/// 2. ���ҽ����� �����Ѵ�.
	SaveResources(worldPath);

	/// 3. �����ִ� Entity���� ����� ���� �����Ѵ�.
	worldPath += "/StartEntity/";

	for (const auto& entry : fs::directory_iterator(worldPath))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".ent")
		{
			fs::remove(entry.path());
		}
	}

	for (const std::shared_ptr<Entity>& ent : _world->GetEntities())
	{
		if (ent->GetState() == Entity::EntityState::Active)
		{
			 Save::SaveEntity(worldPath, ent.get());
		}
	}

	_isSaveWorld = true;
}

void ImpToolModule::WorldViewer::SaveResources(const std::filesystem::path& path)
{
	using namespace ImpReflection;
	using namespace ImpEngineModule;
	// 1. Entity���� ����ִ� ��� ������ ��ΰ����´�
	TypeManager* typeMgr = TypeManager::GetInstance();

	std::vector<std::wstring> pathResources;

	for (const auto& ent : _world->GetEntities())
	{
		for (auto& component : ent->GetComponents())
		{
			Type* type = typeMgr->GetType(component.first);

			// ��������� ��������� �����´�.
			FindPathResource(component.second, type, pathResources);
		}
	}

	// 2. ��ΰ� ����ִٸ� �������� �ʴ´�
	pathResources.erase(std::remove_if(pathResources.begin(), pathResources.end(), [](std::wstring path)
		{
			if (path.empty()) return true;
			return false;
		}), pathResources.end());


	// 3. ��ε��� ��� ����η� �ٲ�����Ѵ�.
	for (auto& path : pathResources)
	{
		PathManager::EraseResourcePath(path);
	}

	// 4. ���� ���Ŀ� ���� �з��ؼ� �����Ѵ�.
	SaveEntityResources(pathResources, path);


}


void ImpToolModule::WorldViewer::SaveEntityResources(const std::vector<std::wstring>& pathResources,
	const std::filesystem::path& currentWorldPath)
{
	std::filesystem::path loadEntityPath = currentWorldPath;
	loadEntityPath += "/LoadEntityList.txt";

	std::wofstream  loadEntityText(loadEntityPath);

	assert(loadEntityText.is_open() && "���Ͽ��� ����");
	for (auto& path : pathResources)
	{
		// .ent Ȯ���ڸ� ������ �Ѵ�
		if (path.substr(path.find_last_of('.')) != L".ent")
		{
			continue;
		}

		loadEntityText << path << '\n';
	}
	loadEntityText.close();

}

void ImpToolModule::WorldViewer::FindPathResource(void* object, ImpReflection::Type* type, std::vector<std::wstring>& resources)
{
	using namespace ImpReflection;
	switch (type->GetTypeCategory())
	{
	case TypeCategory::Class:
	{
		ClassType* classType = reinterpret_cast<ClassType*>(type);
		for (auto& member : classType->GetMembers())
		{
			FindPathResource((char*)object + member._offset, member._type, resources);
		}
	}
	break;
	case TypeCategory::Primitive: // wstring �� �ϴ� �� ��ƿ´�.
	{
		if (type->GetFullName() == "std::wstring")
		{
			std::wstring* data = reinterpret_cast<std::wstring*>(object);
			resources.push_back(data->c_str());
		}
		break;
	}
	}

}

