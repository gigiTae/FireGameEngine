#pragma once


namespace ToolModule
{
	/// <summary>
	/// Scene ������ �ε�, ������ �����ִ� Editor
	/// </summary>
	class WorldEditor
	{
	public:
		WorldEditor();
		~WorldEditor();


		void Show(Fire::ECS::World* world);
	private:
		bool saveSucessfulPopup = false;

	};

}
