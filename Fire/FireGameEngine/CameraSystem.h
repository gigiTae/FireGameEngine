#pragma once

namespace Fire
{
	namespace ECS
	{
		class CameraSystem : public IEntitySystem
		{
		public:
			CameraSystem(RendererModule::Camera* camera);
			~CameraSystem();

		private:
			void Tick(World* world, float dt) override;

			
			RendererModule::Camera* cameraModule;
		};


	}
}

