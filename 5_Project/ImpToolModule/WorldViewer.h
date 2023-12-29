#pragma once

namespace ImpToolModule
{

	/// <summary>
	/// 월드의 관련된 정보를 표시하는 GUI
	/// </summary>
	class WorldViewer
	{
	public:
		WorldViewer();
		~WorldViewer();

	public:
		/// 초기화
		void Initialize(ImpEngineModule::EngineModule* engineModule);

		/// 월드의 GUI를 업데이트한다.
		void Update();
		
	private:
		/// 현재 월드를 저장한다.
		void SaveWorldButton();
		/// 로드 월드 버튼
		void LoadWorldButton();
		/// 월드 생성버튼
		void CreateWorldButton();

		/// 새로운 월드를 생성한다.
		void CreateWorld();

		/// 월드 저장
		void SaveWorld();

		/// 리소스 저장;
		void SaveResources(const std::filesystem::path& path);

		/// 컴포넌트 정보를 순회하면서 들고있는 경로 정보를 벡터에 담는다.
		void FindPathResource(void* object, ImpReflection::Type* type, std::vector<std::wstring>& resources);

		// 현재 월드의 이름을 표시한다.
		void ShowWorldNameToText();

		// 엔티티 리소를 저장한다
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