//// ConsoleApp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
////
//
//#include <iostream>
//#include "World.h"
//#include "Entity.h"
//#include "ComponentHandle.h"
//#include "IEntitySystem.h"
//#include "EntityComponentIterator.h"
//
//
//using World = Fire::ECS::World;
//using Entity = Fire::ECS::Entity;
//
//struct Transform
//{
//public:
//	Transform() = default;
//	Transform(float x, float y, float z) : x(x), y(y), z(z) {}
//
//	float x;
//	float y;
//	float z;
//};
//
//struct Power
//{
//	Power() :x(0.f) {}
//	Power(float x) :x(x) {}
//	float x;
//};
//
//struct SomEvent
//{
//	int num;
//};
//
//class TestSystem : public Fire::ECS::IEntitySystem,
//	public Fire::ECS::EventSubscriber<Fire::ECS::Events::OnEntityCreated>,
//	public Fire::ECS::EventSubscriber<Fire::ECS::Events::OnEntityDestroyed>
//{
//public:
//	virtual ~TestSystem() {}
//
//	void Configure(World* world) override
//	{
//		world->Subscribe<Fire::ECS::Events::OnEntityCreated>(this);
//		world->Subscribe<Fire::ECS::Events::OnEntityDestroyed>(this);
//	}
//
//	void Unconfigure(World* world) override
//	{
//		world->UnsubscribeAll(this);
//	}
//
//	void Tick(World* world, float dt) override
//	{
//		world->Each<Transform, Power>(
//			[&](Entity* ent, Fire::ECS::ComponentHandle<Transform> transform,
//				Fire::ECS::ComponentHandle<Power> power)->void
//			{
//				transform->x = 1.f;
//				transform->y = power->x;
//
//				std::cout << "id : " << ent->GetId() << transform->x << std::endl;
//			});
//	}
//
//	void Receive(World* world, const Fire::ECS::Events::OnEntityCreated& event) override
//	{
//		std::cout << "An entity was created" << std::endl;
//	}
//	
//	void Receive(World* world, const Fire::ECS::Events::OnEntityDestroyed& event) override
//	{
//		std::cout << "An entity was destroyed" << std::endl;
//	}
//
//};
//
//int main()
//{
//	World* world = new World();
//
//	using Fire::ECS::IEntitySystem;
//
//	IEntitySystem* system = world->RegisterSystem(new TestSystem());
//
//	for (int i = 0; i < 5; ++i)
//	{
//		Entity* ent = world->Create();
//		ent->Assign<Transform>(1.f, 1.f, 1.f);
//		ent->Assign<Power>(0.f);
//	}
//
//	world->Tick(1.f);
//
//	world->Reset();
//
//}
//
