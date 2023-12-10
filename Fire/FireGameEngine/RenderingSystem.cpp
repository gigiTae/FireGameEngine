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
	// ������ ���� ������ World���� ��� �������Ѵ�.

	/// 1.������ ������ �ʿ��� ������ Ȯ���Ѵ� ex:camera setting
	world->Each<Camera,Transform>([this](Entity* ent,
		ComponentHandle<Camera> camera, ComponentHandle<Transform> transform)
		{
			// ���� ī�޶� ����
			if (camera->isMain)
			{
				Vector3 pos = transform->position;
				rendererModule->GetCamera()->SetPosition(pos.x, pos.y, pos.z);
				// �ü����͵� �����ؾ��� ������? �� fov�� ���� ��������...
			}
		});

	/// 2.Entity���� ��ȸ�ϸ鼭 Transform ������Ʈ���� ������ Entity�� Ȯ���Ѵ�.
	/// �ʿ��ϴٸ� ����ĸ���� ����ؼ� ���ο� �ٸ� �������� ���հ����ϴ�.
	world->Each<Transform,SphereMesh>([](Entity* ent,
		ComponentHandle<Transform> transform, ComponentHandle<SphereMesh> sphere)
		{
			// Transform�� �������� ������ ������ �ձ� ������ ���Ͻ�Ű��


		}, false);

	/// 3.���߿� ���۵� ������������ �̷��� �ܰ���� ������ ��ġ�� �ɰ��̴�.

	
}
