#pragma once

namespace Fire
{
	namespace Reflect
	{
		struct TypeDescriptor;
	}
}


namespace ToolModule
{
	/// <summary>
	/// Entity�� Component�� �����ϴ� Editor
	/// </summary>
	class ComponentEditor
	{
	public:
		ComponentEditor() {}
		~ComponentEditor(){}

	public:
		void Show(Fire::ECS::Entity* ent);

	private:
		/// <summary>
		/// ������� ������ UI
		/// </summary>
		void DisplayUI(void* obj,const std::string& name, Fire::Reflect::TypeDescriptor* desc);
		void DisplayPrimitiveUI(void* obj,const std::string& name, Fire::Reflect::TypeDescriptor* desc);
	};
}