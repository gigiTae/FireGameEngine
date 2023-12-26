#pragma once

namespace ImpEngineModule
{
	class World;
	class Entity;
	class ResourceManager;

	/// <summary>
	/// World �����͸� �����ϰ� �ε����� ����
	/// </summary>
	class WorldManager
	{
	public:
		WorldManager();
		~WorldManager();

		void Initialize(const std::wstring& startWorld,ImpEngineModule::World* world,
			ImpEngineModule::ResourceManager* resMgr);
		void Finalize();

	public:
		// EntityResouece�� Entity�� �ҷ��´�
		void LoadToEntityResource(const std::filesystem::path& path, ImpEngineModule::Entity* ent);

		// Entity�� World�� �ٷ� �ҷ��´�(World Start ������ ȣ��)
		void LoadEntity(const std::filesystem::path& path, Entity* ent)const;

		// ���� �������� �ε��� Entity���� �޸𸮿� �ø���, ���� Entity��� World�� �����Ѵ�.
		void LoadWorld();

		// Entity���� �������θ� �ε��Ѵ�.
		void BuildEntityHierachy(const std::filesystem::path& path);

		// ���带 ��ȯ�Ѵ�.
		void ChangeWorld(const std::wstring& worldName);

		// ���� ������ �̸�����ȯ
		const std::wstring& GetWorldName()const { return _currentWorld; }

	private:
		std::wstring _currentWorld; // ���� ����
		ImpEngineModule::World* _world;
		ImpEngineModule::ResourceManager* _resourceManager;
		ImpReflection::TypeManager* _typeManager;
	};


}