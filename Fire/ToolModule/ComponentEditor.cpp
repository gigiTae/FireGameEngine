#include "ToolModulepch.h"
#include "ComponentEditor.h"
#include "../EntityComponentSystem/ReflectionHeader.h"
#include "../EntityComponentSystem/ComponentHeader.h"

ToolModule::ComponentEditor::ComponentEditor()
{
	/// Reflection Component List
	for (auto& iter : Fire::Reflect::TypeMap::GetTypeMap()->GetTypeIndexMap())
	{
		// 구조체 타입으로 리플렉션된 멤버들을 가져온다.
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

	// 재귀적인 형태
	switch (desc->category)
	{
	case TYPE_CATEGORY::ENUMCLASS:
	{
		auto members = desc->GetEnumMember();

		int* currentEnum = static_cast<int*>(obj); // 현재 이넘
		int currenIndex = INT_MIN; // 이넘에 해당하는 배열의 인덱스
		std::vector<std::string> memberNames{}; // 멤버들 이름
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

		if (currenIndex == INT_MIN) // 초기화를 안한 경우
		{
			currenIndex = indexMatch[0]; 
		}

		if (ImGui::BeginCombo(name.c_str(), memberNames[currenIndex].c_str()))
		{
			for (int i = 0; i < members.size(); ++i)
			{
				// 각 항목에 대한 선택 가능한 버튼을 생성
				const bool isSelected = (currenIndex == i);
				if (ImGui::Selectable(memberNames[i].c_str(), isSelected))
				{
					currenIndex = i;
				}

				// 선택된 항목에 체크 마크 표시
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus(); // 선택된 항목에 초점을 맞춤
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
			// 구조체 내부의 리플렉션된 멤버들을 재귀적으로 UI를 그린다.
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

		assert(!"TYPE에 대한 정의가 필요합니다");
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
			// 각 항목에 대한 선택 가능한 버튼을 생성
			const bool isSelected = (addComponentIndex == i);
			if (ImGui::Selectable(reflectComponents[i].c_str(), isSelected))
			{
				addComponentIndex = i;
			}

			// 선택된 항목에 체크 마크 표시
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus(); // 선택된 항목에 초점을 맞춤
			}
		}

		ImGui::EndCombo();
	}

	ImGui::SameLine();

	// TODO:: C++의 아쉬운점이다. 결국에는 한번은 노가다를 해야한다.
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
