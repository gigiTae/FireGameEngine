#pragma once

namespace ImpEngineModule
{
	class Entity;
	class World;

	/// <summary>
	/// ī�޶� �����ϴ� �Ŵ���
	/// </summary>
		class CameraManager
	{
	public:
		CameraManager();
		~CameraManager();

		void Initialize(World* world);
		void Update();
		void Finalize();

		// MainCamera�� ã�´�
		Entity* FindMainCamera();

		// ���� ī�޶� ���´�.
		Entity* GetMainCamera();
	private:
		Entity* _mainCamera;

		World* _world;
	};


}