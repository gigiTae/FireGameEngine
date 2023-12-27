#pragma once

namespace ImpEngineModule
{
	class EntityResource;

	/// <summary>
	/// ���ҽ��� �����ϴ� Ŭ����
	/// 
	/// </summary>
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		/// �ʱ�ȭ
		void Initailize(const std::wstring startWorld);
		
		/// ����
		void Finalize();

		/// Entity���ҽ��� ��η� ��´�.
		EntityResource* GetEntityResource(const std::wstring& path);

		/// ���ҽ��� Ȯ���ڿ� �´� ���ҽ��� �ε��Ѵ�.
		void LoadResource(const std::wstring& path);

		/// �ε��� Entity���� ���� List�� �ε��Ѵ�.
		void LoadEntityList(const std::wstring& path);

		/// Entity ���ҽ��� �ε��Ѵ�.
		void LoadEntityResource(const std::wstring& path);

		/// ��� EntityResourc�� ��ε��Ѵ�. 
		void UnloadAllEntityResources();

	private:
		std::vector<std::filesystem::path> _worldDataList;
		std::unordered_map<std::wstring, std::unique_ptr<EntityResource>> _entityData;

	};


}