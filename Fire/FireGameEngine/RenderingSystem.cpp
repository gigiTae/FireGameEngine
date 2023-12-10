#include "FireGameEnginepch.h"
#include "RenderingSystem.h"


Fire::ECS::RenderingSystem::RenderingSystem(RendererModule::D3DRenderer* renderer)
	: IEntitySystem(), rendererModule(renderer)
{
}

Fire::ECS::RenderingSystem::~RenderingSystem()
{

}

void Fire::ECS::RenderingSystem::Configure(World* world)
{

}

void Fire::ECS::RenderingSystem::Unconfigure(World* world)
{

}

void Fire::ECS::RenderingSystem::Tick(World* world, float dt)
{
	using namespace Fire::ECS;
	using namespace Fire::Component;
	// 랜더링 관련 정보를 World에서 얻고 랜더링한다.

	/// 1.랜더링 이전에 필요한 설정을 확인한다 ex:camera setting
	world->Each<Camera,Transform>([this](Entity* ent,
		ComponentHandle<Camera> camera, ComponentHandle<Transform> transform)
		{
			// 메인 카메라 설정
			if (camera->isMain)
			{
				Vector3 pos = transform->position;
				rendererModule->GetCamera()->SetPosition(pos.x, pos.y, pos.z);
				// 시선벡터도 설정해야지 귀찮음? 또 fov는 ㅋㅋ 내일하자...
			}
		});

	/// 2.Entity들을 순회하면서 Transform 컴포넌트들을 가지는 Entity만 확인한다.
	/// 필요하다면 람다캡러를 사용해서 내부에 다른 정보들을 결합가능하다.
	world->Each<Transform,SphereMesh>([](Entity* ent,
		ComponentHandle<Transform> transform, ComponentHandle<SphereMesh> sphere)
		{
			// Transform의 정보만을 가지고 랜더링 둥근 원으로 통일시키자


		}, false);

	/// 3.나중에 디퍼드 랜더링에서는 이러한 단계들을 여러번 거치게 될것이다.

	
}
