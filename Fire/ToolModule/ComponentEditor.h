#pragma once

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


	};


}