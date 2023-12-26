#pragma once

namespace ImpToolModule
{

	/// <summary>
	/// World의 Entity들의 정보를 보여주는 GUI
	/// 
	/// </summary>
	class EntityViewer
	{
	public:
		EntityViewer();
		~EntityViewer();

	public:
		void Initialize(ImpEngineModule::EngineModule* engineModule);

		void Update();

		ImpEngineModule::Entity* GetSelectEntity() const { return _selectEntity; }
	private:
		// 엔티티 GUI를 그린기
		void ShowEntityGUI(ImpEngineModule::Entity* ent);

		// 자식이 없는 Entity GUI그리기
		void ShowEntityGUIWithoutChild(ImpEngineModule::Entity* ent);

		// 저장버튼
		void SaveEntityButton(ImpEngineModule::Entity* ent);
		
		// 로드 버튼
		void LoadEntityButton(ImpEngineModule::World* world);
		
		// 엔티티경로 받기
		void DropEntity(ImpEngineModule::World* world);

		// Entity 계층구조 드래그 드랍
		void DragDropEntityHeirachy(ImpEngineModule::Entity* ent);

		// Entity 검색기능
		void SearchEntityGUI();

	private:
		ImpEngineModule::World* _world = nullptr;
		ImpEngineModule::Entity* _selectEntity = nullptr;
		ImpEngineModule::WorldManager* _worldManager = nullptr;

		bool _isShowPopup = false;
		std::string _searchName;
	};


}