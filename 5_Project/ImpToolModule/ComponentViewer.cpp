#include "ImpToolModulePCH.h"
#include "ComponentViewer.h"
#include "Rebind.h"

ImpToolModule::ComponentViewer::ComponentViewer()
	:_viewComponent(nullptr), _reflectComponents{}, _graphicsEngine(nullptr)
	, _viewEntity(nullptr), _isRebindEntity(false)
{
	using namespace ImpReflection;

	TypeManager* mgr = TypeManager::GetInstance();

	// ���÷��ǵ� ������Ʈ�� �̸����� �����´�.
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

		// Component ���� ǥ��
		for (auto& iter : components)
		{
			std::type_index index = iter.first;
			Type* type = typeMgr->GetType(index);

			std::string name = type->GetFullName();
			Component* component = iter.second;
			_viewComponent = component;

			ViewComponentInfomation(component, name, type);

			// ������Ʈ ���� (Ʈ�������� �����Ѵ�)
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

		// ������ ������Ʈ ����
		if (eraseIndex != ImpEngineModule::EXCEPTION)
		{
			Component* component = ent->GetComponent(eraseIndex);
			Mesh* mesh = dynamic_cast<Mesh*>(component);

			// �޽��� �����ϴ� ��� ���ε��� �����Ѵ�.
			if (mesh != nullptr)
			{
				mesh->SetActive(false);
				Bind::RebindMeshObject(ent, _graphicsEngine);
			}

			ent->DestroyComponent(eraseIndex);
		}

	}

	ImGui::End();


	// �ٽ� �׷��Ƚ� ������ ���ε��� �ʿ��� ���
	if (_isRebindEntity)
	{
		Bind::Rebind(ent, _graphicsEngine);
	}
}

void ImpToolModule::ComponentViewer::ViewComponentInfomation(void* object, const std::string& name, ImpReflection::Type* type)
{
	using namespace ImpReflection;

	// ������� ����

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

		int* currentEnum = static_cast<int*>(object); // ����
		int currentIndex = INT_MIN; // �̳ѿ� �ش��ϴ� �迭�� �ε���
		std::vector<std::string> memberNames{}; // ����� �̸�
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

		if (currentIndex == INT_MIN) // �ʱ�ȭ�� ���� ���
		{
			currentIndex = indexMatch[0];
		}

		std::string fureName = ImpStringHelper::EraseUnderbar(name);

		if (ImGui::BeginCombo(fureName.c_str(), memberNames[currentIndex].c_str()))
		{
			for (int i = 0; i < members.size(); ++i)
			{
				// �� �׸� ���� ���� ������ ��ư�� ����
				const bool isSelected = (currentIndex == i);
				if (ImGui::Selectable(memberNames[i].c_str(), isSelected))
				{
					currentIndex = i;
				}

				// ���õ� �׸� üũ ��ũ ǥ��
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus(); // ���õ� �׸� ������ ����
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
		assert(!"Tpye�� ���� ������ �����ϴ�.");
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
		// imgui���� �� ã�ƺ��� long long �̶���� �����Ҳ� ����?
		// ������ ������� �����ϴ°��� �ʿ��ϸ� �����մϴ�.
		assert(!"�����ϴ� ������ �����ϴ�.");
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
			// �� �׸� ���� ���� ������ ��ư�� ����
			const bool isSeleted = (_addComponentIndex == i);
			if (ImGui::Selectable(_reflectComponents[i].c_str(), isSeleted))
			{
				_addComponentIndex = i;
			}

			// ���õ� �׸� üũ ��ũ ǥ��
			if (isSeleted)
			{
				ImGui::SetItemDefaultFocus(); // ���õ� �׸� ������ ����
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

		// �̹� ������ ������Ʈ�� �ߺ����� �߰����� �ʴ´�.
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
