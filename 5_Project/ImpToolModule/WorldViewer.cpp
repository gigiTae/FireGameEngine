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

	// 세이브에 성공하면 팝업창 띄우기
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
				// 월드를 생성한다.
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
	// 1. 월드를 폴더를 생성한다.
	using namespace ImpEngineModule;
	namespace fs = std::filesystem;

	auto path = PathManager::GetWorldDataPath();
	path += "/";
	path += _inputWorldName;

	fs::create_directory(path);

	// LoadEntityList.txt 파일생성
	fs::path listPath = path;
	listPath += "/LoadEntityList.txt";
	std::wofstream  loadList(listPath);

	// StartEntity 폴더 생성
	path += "/StartEntity";
	fs::create_directory(path);

	_currentWorldName = fs::path(_inputWorldName);
	_worldManager->ChangeWorld(_currentWorldName);
}

void ImpToolModule::WorldViewer::SaveWorld()
{
	using namespace ImpEngineModule;
	namespace fs = std::filesystem;

	/// 1.월드 경로를 생성한다.
	fs::path  worldPath = PathManager::GetWorldDataPath();
	worldPath += "/";
	worldPath += _currentWorldName;

	/// 2. 리소스들을 저장한다.
	SaveResources(worldPath);

	/// 3. 원래있던 Entity들을 지우고 새로 생성한다.
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
	// 1. Entity들이 들고있는 경로 정보를 모두가져온다
	TypeManager* typeMgr = TypeManager::GetInstance();

	std::vector<std::wstring> pathResources;

	for (const auto& ent : _world->GetEntities())
	{
		for (auto& component : ent->GetComponents())
		{
			Type* type = typeMgr->GetType(component.first);

			// 재귀적으로 경로정보를 가져온다.
			FindPathResource(component.second, type, pathResources);
		}
	}

	// 2. 경로가 비어있다면 저장하지 않는다
	pathResources.erase(std::remove_if(pathResources.begin(), pathResources.end(), [](std::wstring path)
		{
			if (path.empty()) return true;
			return false;
		}), pathResources.end());


	// 3. 경로들을 모두 상대경로로 바꿔줘야한다.
	for (auto& path : pathResources)
	{
		PathManager::EraseResourcePath(path);
	}

	// 4. 파일 형식에 따라서 분류해서 저장한다.
	SaveEntityResources(pathResources, path);


}


void ImpToolModule::WorldViewer::SaveEntityResources(const std::vector<std::wstring>& pathResources,
	const std::filesystem::path& currentWorldPath)
{
	std::filesystem::path loadEntityPath = currentWorldPath;
	loadEntityPath += "/LoadEntityList.txt";

	std::wofstream  loadEntityText(loadEntityPath);

	assert(loadEntityText.is_open() && "파일열기 실패");
	for (auto& path : pathResources)
	{
		// .ent 확장자만 저장을 한다
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
	case TypeCategory::Primitive: // wstring 은 일단 다 담아온다.
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

