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
	/// Entity의 Component를 편집하는 Editor
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
		/// 재귀적인 구조의 UI
		/// </summary>
		void DisplayUI(void* obj,const std::string& name, Fire::Reflect::TypeDescriptor* desc);
		void DisplayPrimitiveUI(void* obj,const std::string& name, Fire::Reflect::TypeDescriptor* desc);
	};
}