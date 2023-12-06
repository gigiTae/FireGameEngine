#include "ToolModulepch.h"
#include "ComponentEditor.h"
#include "../Reflection/ReflectionHeader.h"


void ToolModule::ComponentEditor::Show(Fire::ECS::Entity* ent)
{
	ImGui::Begin("Component");
	if (ent != nullptr)
	{
		std::string entInfo = "ID:" + std::to_string(ent->GetId());
		ImGui::Text(entInfo.c_str());

		auto& components = ent->GetComponents();

		Fire::Reflect::TypeMap* typeMap = Fire::Reflect::TypeMap::GetTypeMap();

		for (auto& iter : components)
		{
			auto typeIndex = iter.first;
			Fire::Reflect::TypeDescriptor* desc = typeMap->GetTypeDescriptor(typeIndex);
			std::string name = desc->GetFullName();
			auto& compoent = (*iter.second);

			DisplayUI(compoent.GetAddress(), name, desc);
		}
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

		std::vector<std::string> memberNames{};

		for (auto& member : members)
		{
			std::string name = member.first + "(";
			name += std::to_string(member.second);
			name += ")";

			memberNames.push_back(name);
		}

		int size = static_cast<int>(members.size());

		//if (ImGui::Combo(name.c_str(), &size,))	

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

