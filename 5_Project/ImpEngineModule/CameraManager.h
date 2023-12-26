#pragma once

namespace ImpEngineModule
{
	class Entity;
	class World;

	/// <summary>
	/// 카메라를 관리하는 매니져
	/// </summary>
		class CameraManager
	{
	public:
		CameraManager();
		~CameraManager();

		void Initialize(World* world);
		void Update();
		void Finalize();

		// MainCamera를 찾는다
		Entity* FindMainCamera();

		// 메인 카메라를 얻어온다.
		Entity* GetMainCamera();
	private:
		Entity* _mainCamera;

		World* _world;
	};


}