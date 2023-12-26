#pragma once

namespace ImpToolModule
{

	/// <summary>
	/// World�� Entity���� ������ �����ִ� GUI
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
		// ��ƼƼ GUI�� �׸���
		void ShowEntityGUI(ImpEngineModule::Entity* ent);

		// �ڽ��� ���� Entity GUI�׸���
		void ShowEntityGUIWithoutChild(ImpEngineModule::Entity* ent);

		// �����ư
		void SaveEntityButton(ImpEngineModule::Entity* ent);
		
		// �ε� ��ư
		void LoadEntityButton(ImpEngineModule::World* world);
		
		// ��ƼƼ��� �ޱ�
		void DropEntity(ImpEngineModule::World* world);

		// Entity �������� �巡�� ���
		void DragDropEntityHeirachy(ImpEngineModule::Entity* ent);

		// Entity �˻����
		void SearchEntityGUI();

	private:
		ImpEngineModule::World* _world = nullptr;
		ImpEngineModule::Entity* _selectEntity = nullptr;
		ImpEngineModule::WorldManager* _worldManager = nullptr;

		bool _isShowPopup = false;
		std::string _searchName;
	};


}