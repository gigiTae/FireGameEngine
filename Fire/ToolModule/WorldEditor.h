#pragma once


namespace ToolModule
{
	/// <summary>
	/// Scene 데이터 로드, 저장을 도와주는 Editor
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
