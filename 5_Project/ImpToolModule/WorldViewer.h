#pragma once

namespace ImpToolModule
{

	/// <summary>
	/// ������ ���õ� ������ ǥ���ϴ� GUI
	/// </summary>
	class WorldViewer
	{
	public:
		WorldViewer();
		~WorldViewer();

	public:
		/// �ʱ�ȭ
		void Initialize(ImpEngineModule::EngineModule* engineModule);

		/// ������ GUI�� ������Ʈ�Ѵ�.
		void Update();
		
	private:
		/// ���� ���带 �����Ѵ�.
		void SaveWorldButton();
		/// �ε� ���� ��ư
		void LoadWorldButton();
		/// ���� ������ư
		void CreateWorldButton();

		/// ���ο� ���带 �����Ѵ�.
		void CreateWorld();

		/// ���� ����
		void SaveWorld();

		/// ���ҽ� ����;
		void SaveResources(const std::filesystem::path& path);

		/// ������Ʈ ������ ��ȸ�ϸ鼭 ����ִ� ��� ������ ���Ϳ� ��´�.
		void FindPathResource(void* object, ImpReflection::Type* type, std::vector<std::wstring>& resources);

		// ���� ������ �̸��� ǥ���Ѵ�.
		void ShowWorldNameToText();

		// ��ƼƼ ���Ҹ� �����Ѵ�
		void SaveEntityResources(const std::vector<std::wstring>& pathResources,
			const std::filesystem::path& currentWorldPath);

	private:
		ImpEngineModule::World* _world =nullptr;
		ImpEngineModule::WorldManager* _worldManager = nullptr;
		ImpEngineModule::ResourceManager* _resourceManager = nullptr;

		std::wstring _currentWorldName;
		std::string _inputWorldName;
		bool _isOpenCreatePopup = false;
		bool _isSaveWorld = false;
	};


}