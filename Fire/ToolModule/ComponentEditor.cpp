#include "ToolModulepch.h"
#include "ComponentEditor.h"
#include "../EntityComponentSystem/ReflectionHeader.h"
#include "../EntityComponentSystem/ComponentHeader.h"

ToolModule::ComponentEditor::ComponentEditor()
{
	/// Reflection Component List
	for (auto& iter : Fire::Reflect::TypeMap::GetTypeMap()->GetTypeIndexMap())
	{
		// ����ü Ÿ������ ���÷��ǵ� ������� �����´�.
		if (Fire::Reflect::TypeMap::GetTypeMap()->GetTypeDescriptor(iter.second)->category != Fire::Reflect::TYPE_CATEGORY::STRUCT)
			continue;;

		reflectComponents.push_back(iter.second);
	}

}

void ToolModule::ComponentEditor::Show(Fire::ECS::Entity* ent)
{
	ImGui::Begin("Component");
	if (ent != nullptr)
	{
		std::string entInfo = "Entity ID : " + std::to_string(ent->GetId());
		ImGui::Text(entInfo.c_str());

		auto& components = ent->GetComponents();

		Fire::Reflect::TypeMap* typeMap = Fire::Reflect::TypeMap::GetTypeMap();

		ImGui::Separator();

		/// Component Relfection 
		for (auto& iter : components)
		{
			auto typeIndex = iter.first;
			Fire::Reflect::TypeDescriptor* desc = typeMap->GetTypeDescriptor(typeIndex);
			std::string name = desc->GetFullName();
			auto& compoent = (*iter.second);

			DisplayUI(compoent.GetAddress(), name, desc);

			ImGui::SameLine();
			if(ImGui::Button("-"))
			{
				ent->RemoveComponent();
			}
			ImGui::Separator();
		}

		DisplayAddComponent(ent);
	}

	ImGui::End();
}

void ToolModule::ComponentEditor::DisplayUI(void* obj, const std::string& name, Fire::Reflect::TypeDescriptor* desc)
{
	using namespace Fire::Reflect;

	// ������� ����
	switch (desc->category)
	{
	case TYPE_CATEGORY::ENUMCLASS:
	{
		auto members = desc->GetEnumMember();

		int* currentEnum = static_cast<int*>(obj); // ���� �̳�
		int currenIndex = INT_MIN; // �̳ѿ� �ش��ϴ� �迭�� �ε���
		std::vector<std::string> memberNames{}; // ����� �̸�
		std::vector<int> indexMatch; 

		for (auto& member : members)
		{
			std::string name = member.first + "(";
			name += std::to_string(member.second);
			name += ")";

			memberNames.push_back(name.c_str());
			indexMatch.push_back(member.second);

			if (*currentEnum == member.second)
			{
				currenIndex = memberNames.size()-1;
			}
		}
	
		int size = static_cast<int>(members.size());

		if (currenIndex == INT_MIN) // �ʱ�ȭ�� ���� ���
		{
			currenIndex = indexMatch[0]; 
		}

		if (ImGui::BeginCombo(name.c_str(), memberNames[currenIndex].c_str()))
		{
			for (int i = 0; i < members.size(); ++i)
			{
				// �� �׸� ���� ���� ������ ��ư�� ����
				const bool isSelected = (currenIndex == i);
				if (ImGui::Selectable(memberNames[i].c_str(), isSelected))
				{
					currenIndex = i;
				}

				// ���õ� �׸� üũ ��ũ ǥ��
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus(); // ���õ� �׸� ������ ����
				}
			}

			ImGui::EndCombo();
		}

		*currentEnum = indexMatch[currenIndex];


		break;
	}
	case TYPE_CATEGORY::STRUCT:
	{
		TypeDescriptor_Struct* structDesc = reinterpret_cast<TypeDescriptor_Struct*>(desc);

		if (ImGui::TreeNode(StringHelper::EraseNamespace(name).c_str()))
		{
			// ����ü ������ ���÷��ǵ� ������� ��������� UI�� �׸���.
			for (auto& member : structDesc->members)
			{
				std::string memberName(member.name);
				DisplayUI((char*)obj + member.offset, memberName, member.desc);
			}

			ImGui::TreePop();
		}
		break;
	}
	case TYPE_CATEGORY::PRIMITIVE:
	{
		DisplayPrimitiveUI(obj, name, desc);
		break;
	}
	case TYPE_CATEGORY::NONE:
	{

		assert(!"TYPE�� ���� ���ǰ� �ʿ��մϴ�");
		break;
	}
	default:
		break;
	}

}

void ToolModule::ComponentEditor::DisplayPrimitiveUI(void* obj, const std::string& name, Fire::Reflect::TypeDescriptor* desc)
{
	if (desc->name =="int")
	{
		int* data = reinterpret_cast<int*>(obj);
		ImGui::InputInt(name.c_str(), data);
	}
	else if (desc->name == "float")
	{
		float* data = reinterpret_cast<float*>(obj);
		ImGui::InputFloat(name.c_str(), data);
	}
	else if (desc->name == "std::string")
	{
		std::string* data = reinterpret_cast<std::string*>(obj);

		ImGui::InputText(name.c_str(), data);
	}
	else if (desc->name == "bool")
	{
		bool* data = reinterpret_cast<bool*>(obj);
		ImGui::Checkbox(name.c_str(), data);
	}
	else if (desc->name == "std::wstring")
	{
	
	}
	else
	{
		int a = 0;
	}
}

void ToolModule::ComponentEditor::DisplayAddComponent(Fire::ECS::Entity* ent)
{
	if (ImGui::BeginCombo("##combo", reflectComponents[addComponentIndex].c_str()))
	{
		for (int i = 0; i < reflectComponents.size(); ++i)
		{
			// �� �׸� ���� ���� ������ ��ư�� ����
			const bool isSelected = (addComponentIndex == i);
			if (ImGui::Selectable(reflectComponents[i].c_str(), isSelected))
			{
				addComponentIndex = i;
			}

			// ���õ� �׸� üũ ��ũ ǥ��
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus(); // ���õ� �׸� ������ ����
			}
		}

		ImGui::EndCombo();
	}

	ImGui::SameLine();

	// TODO:: C++�� �ƽ������̴�. �ᱹ���� �ѹ��� �밡�ٸ� �ؾ��Ѵ�.
	if (ImGui::Button("+"))
	{
		std::string& componentName = reflectComponents[addComponentIndex];

		if (componentName == "Fire::Component::Transform")
		{
			ent->Assign<Fire::Component::Transform>();
		}

		if (componentName == "Fire::Component::Vector3")
		{
			ent->Assign<Fire::Component::Vector3>();
		}
	}

}
