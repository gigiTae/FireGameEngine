#pragma once



namespace Fire
{
	namespace ECS
	{
		class RenderingSystem : public IEntitySystem
		{
		public:
			RenderingSystem(RendererModule::D3DRenderer* renderer);
			~RenderingSystem();

		public:
			void Configure(World* world) override;
			void Unconfigure(World* world) override;

			void Tick(World* world, float dt) override;

		private:
			RendererModule::D3DRenderer* rendererModule = nullptr;
			// TODO :: RenderingPipline Ãß°¡

		};


	}

}

