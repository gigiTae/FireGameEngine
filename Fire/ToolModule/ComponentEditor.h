#pragma once

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


	};


}