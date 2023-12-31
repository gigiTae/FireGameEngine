#include "ImpToolModulePCH.h"
#include "ComponentViewer.h"
#include "Rebind.h"

ImpToolModule::ComponentViewer::ComponentViewer()
	:_viewComponent(nullptr), _reflectComponents{}, _graphicsEngine(nullptr)
	, _viewEntity(nullptr), _isRebindEntity(false)
{
	using namespace ImpReflection;

	TypeManager* mgr = TypeManager::GetInstance();

	// 리플렉션된 컴포넌트들 이름들을 가져온다.
	for (auto& iter : mgr->GetTypeInfomations())
	{
		if (iter.second.type->GetTypeCategory() != TypeCategory::Class
			|| iter.second.type->GetTag() != ImpReflection::Tag::Component)
		{
			continue;
		}

		_reflectComponents.push_back(iter.first);
	}
}

void ImpToolModule::ComponentViewer::Initialize(ImpGraphics::IImpGraphicsEngine* grahphicsEngnie)
{
	_graphicsEngine = grahphicsEngnie;
}

void ImpToolModule::ComponentViewer::Update(ImpEngineModule::Entity* ent)
{
	using namespace ImpEngineModule;
	using namespace ImpReflection;

	_isRebindEntity = false;
	_viewEntity = ent;

	ImGui::Begin("ComponentViewer");

	if (ent != nullptr)
	{
		ImGui::Text(ent->GetName().c_str());

		auto& components = ent->GetComponents();

		ImpReflection::TypeManager* typeMgr = ImpReflection::TypeManager::GetInstance();

		ImGui::Separator();

		std::type_index eraseIndex = ImpEngineModule::EXCEPTION;

		// Component 정보 표시
		for (auto& iter : components)
		{
			std::type_index index = iter.first;
			Type* type = typeMgr->GetType(index);

			std::string name = type->GetFullName();
			Component* component = iter.second;
			_viewComponent = component;

			ViewComponentInfomation(component, name, type);

			// 컴포넌트 삭제 (트랜스폼은 제외한다)
			if (name == "ImpEngineModule::Transform")
			{
				continue;
			}

			ImGui::SameLine();
			std::string deleteButton = "X##";
			deleteButton += name;
			ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize("XX").x);
			if (ImGui::Button(deleteButton.c_str()))
			{
				eraseIndex = index;
			}

		}

		ImGui::Separator();
		ViewAddComponent(ent);

		// 삭제할 컴포넌트 삭제
		if (eraseIndex != ImpEngineModule::EXCEPTION)
		{
			Component* component = ent->GetComponent(eraseIndex);
			Mesh* mesh = dynamic_cast<Mesh*>(component);

			// 메쉬를 삭제하는 경우 바인딩을 해제한다.
			if (mesh != nullptr)
			{
				mesh->SetActive(false);
				Bind::RebindMeshObject(ent, _graphicsEngine);
			}

			ent->DestroyComponent(eraseIndex);
		}

	}

	ImGui::End();


	// 다시 그래픽스 엔진에 바인딩이 필요한 경우
	if (_isRebindEntity)
	{
		Bind::Rebind(ent, _graphicsEngine);
	}
}

void ImpToolModule::ComponentViewer::ViewComponentInfomation(void* object, const std::string& name, ImpReflection::Type* type)
{
	using namespace ImpReflection;

	// 재귀적인 형태

	switch (type->GetTypeCategory())
	{
	case TypeCategory::Class:
	{
		ClassType* classType = reinterpret_cast<ClassType*>(type);

		std::string fureName = ImpStringHelper::EraseUnderbar(ImpStringHelper::EraseNamespace(name));

		if (ImGui::TreeNode(fureName.c_str()))
		{
			for (auto& member : classType->GetMembers())
			{
				ViewComponentInfomation((char*)object + member._offset, member._name, member._type);
			}

			ImGui::TreePop();
		}

		break;
	}
	case TypeCategory::EnumClass:
	{
		auto& members = type->GetEnumMembers();

		int* currentEnum = static_cast<int*>(object); // 현재
		int currentIndex = INT_MIN; // 이넘에 해당하는 배열의 인덱스
		std::vector<std::string> memberNames{}; // 멤버들 이름
		std::vector<int> indexMatch;

		for (auto& member : members)
		{
			std::string name = member._name + "(";
			name += std::to_string(member._value);
			name += ")";

			memberNames.push_back(name.c_str());
			indexMatch.push_back(member._value);

			if (*currentEnum == member._value)
			{
				currentIndex = static_cast<int>(memberNames.size()) - 1;
			}
		}

		int size = static_cast<int>(members.size());

		if (currentIndex == INT_MIN) // 초기화를 안한 경우
		{
			currentIndex = indexMatch[0];
		}

		std::string fureName = ImpStringHelper::EraseUnderbar(name);

		if (ImGui::BeginCombo(fureName.c_str(), memberNames[currentIndex].c_str()))
		{
			for (int i = 0; i < members.size(); ++i)
			{
				// 각 항목에 대한 선택 가능한 버튼을 생성
				const bool isSelected = (currentIndex == i);
				if (ImGui::Selectable(memberNames[i].c_str(), isSelected))
				{
					currentIndex = i;
				}

				// 선택된 항목에 체크 마크 표시
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus(); // 선택된 항목에 초점을 맞춤
				}
			}

			ImGui::EndCombo();
		}

		*currentEnum = indexMatch[currentIndex];

		break;
	}
	case TypeCategory::Primitive:
	{
		ViewPrimitiveType(object, name, type);
		break;
	}
	case TypeCategory::Map:
	{
		ViewMapType(object, name, type);
		break;
	}
	case TypeCategory::List:
	{
		ViewListType(object, name, type);
		break;
	}
	case TypeCategory::Vector:
	{
		ViewVectorType(object, name, type);
		break;
	}
	case TypeCategory::UnorderedMap:
	{
		ViewUnorderedMapType(object, name, type);
		break;
	}
	case TypeCategory::None:
	{
		assert(!"Tpye에 대한 정보가 없습니다.");
	}
	break;
	default:
	{
		// dd7
	}
	break;
	}
}

void ImpToolModule::ComponentViewer::ViewPrimitiveType(void* object, const std::string& name, ImpReflection::Type* type)
{
	std::string fureName = ImpStringHelper::EraseUnderbar(name);

	if (type->GetFullName() == "int")
	{
		int* data = reinterpret_cast<int*>(object);
		ImGui::InputInt(fureName.c_str(), data);
	}
	else if (type->GetFullName() == "unsigned int")
	{
		unsigned int* data = reinterpret_cast<unsigned int*>(object);
		ImGui::InputScalar(fureName.c_str(), ImGuiDataType_U32, data);
	}
	else if (type->GetFullName() == "float")
	{
		float* data = reinterpret_cast<float*>(object);
		ImGui::DragFloat(fureName.c_str(), data, 0.1f);
	}
	else if (type->GetFullName() == "double")
	{
		double* data = reinterpret_cast<double*>(object);
		ImGui::InputDouble(fureName.c_str(), data);
	}
	else if (type->GetFullName() == "std::string")
	{
		std::string* data = reinterpret_cast<std::string*>(object);

		ImGui::InputText(fureName.c_str(), data);
	}
	else if (type->GetFullName() == "bool")
	{
		bool* data = reinterpret_cast<bool*>(object);
		ImGui::Checkbox(fureName.c_str(), data);
	}
	else if (type->GetFullName() == "std::wstring")
	{
		std::wstring* data = reinterpret_cast<std::wstring*>(object);

		std::string sData = std::filesystem::path(*data).filename().string();

		if (ImGui::InputText(fureName.c_str(), &sData))
		{
		}

		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payLoad = ImGui::AcceptDragDropPayload("ResourcePath");
			if (payLoad)
			{
				const wchar_t* receiveData = static_cast<const wchar_t*>(payLoad->Data);

				std::wstring path = receiveData;
				*data = path;

				_isRebindEntity = true;
			}
		}

	}
	else
	{
		// imgui에서 더 찾아보면 long long 이라던지 가능할꺼 같다?
		// 하지만 여기까지 구현하는것은 필요하면 시작합니다.
		assert(!"지원하는 형식이 없습니다.");
	}
}

void ImpToolModule::ComponentViewer::ViewVectorType(void* object, const std::string& name, ImpReflection::Type* type)
{
	std::string output = type->GetFullName();

	ImGui::Text(output.c_str());
	ImGui::SameLine();
	ImGui::Text(name.c_str());
}

void ImpToolModule::ComponentViewer::ViewListType(void* object, const std::string& name, ImpReflection::Type* type)
{
	std::string output = type->GetFullName();

	ImGui::Text(output.c_str());
	ImGui::SameLine();
	ImGui::Text(name.c_str());
}

void ImpToolModule::ComponentViewer::ViewMapType(void* object, const std::string& name, ImpReflection::Type* type)
{
	std::string output = type->GetFullName();

	ImGui::Text(output.c_str());
	ImGui::SameLine();
	ImGui::Text(name.c_str());
}

void ImpToolModule::ComponentViewer::ViewUnorderedMapType(void* object, const std::string& name, ImpReflection::Type* type)
{
	std::string output = type->GetFullName();

	ImGui::Text(output.c_str());
	ImGui::SameLine();
	ImGui::Text(name.c_str());
}

void ImpToolModule::ComponentViewer::ViewAddComponent(ImpEngineModule::Entity* ent)
{
	if (ImGui::BeginCombo("##combo", _reflectComponents[_addComponentIndex].c_str()))
	{
		for (int i = 0; i < _reflectComponents.size(); ++i)
		{
			// 각 항목에 대한 선택 가능한 버튼을 생성
			const bool isSeleted = (_addComponentIndex == i);
			if (ImGui::Selectable(_reflectComponents[i].c_str(), isSeleted))
			{
				_addComponentIndex = i;
			}

			// 선택된 항목에 체크 마크 표시
			if (isSeleted)
			{
				ImGui::SetItemDefaultFocus(); // 선택된 항목에 초점을 맞춤
			}
		}
		ImGui::EndCombo();
	}

	ImGui::SameLine();

	if (ImGui::Button("+"))
	{
		std::string& componentName = _reflectComponents[_addComponentIndex];

		ImpReflection::TypeManager* mgr = ImpReflection::TypeManager::GetInstance();

		ImpReflection::Type* type = mgr->GetType(componentName);

		auto index = mgr->GetTypeIndex(componentName);

		// 이미 소유한 컴포넌트는 중복으로 추가하지 않는다.
		if (!ent->HasComponent(index))
		{
			ent->AddComponent(type->Invoke(), index);

			if ("ImpEngineModule::Mesh" == componentName)
			{
				Bind::RebindMeshObject(ent, _graphicsEngine);
			}

		}
	}
}
