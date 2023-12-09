#pragma once


namespace ToolModule
{

	class EntityEditor
	{
	public:
		EntityEditor();
		~EntityEditor();

	public:
		void Show(Fire::ECS::World* world);

		Fire::ECS::Entity* GetSelectEntity() const { return selectEnt; }

	private:
		void LoadEntity(Fire::ECS::World* ent);

	private:
		Fire::ECS::Entity* selectEnt = nullptr;
		std::string loadPath;
	};

}
