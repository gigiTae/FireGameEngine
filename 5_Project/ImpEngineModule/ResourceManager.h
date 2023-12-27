#pragma once

namespace ImpEngineModule
{
	class EntityResource;

	/// <summary>
	/// 리소스를 관리하는 클래스
	/// 
	/// </summary>
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		/// 초기화
		void Initailize(const std::wstring startWorld);
		
		/// 종료
		void Finalize();

		/// Entity리소스를 경로로 얻는다.
		EntityResource* GetEntityResource(const std::wstring& path);

		/// 리소스의 확장자에 맞는 리소스를 로드한다.
		void LoadResource(const std::wstring& path);

		/// 로드할 Entity들을 담은 List를 로드한다.
		void LoadEntityList(const std::wstring& path);

		/// Entity 리소스를 로드한다.
		void LoadEntityResource(const std::wstring& path);

		/// 모든 EntityResourc를 언로드한다. 
		void UnloadAllEntityResources();

	private:
		std::vector<std::filesystem::path> _worldDataList;
		std::unordered_map<std::wstring, std::unique_ptr<EntityResource>> _entityData;

	};


}