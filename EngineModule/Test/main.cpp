#include <iostream>
#include "../EngineModule/EngineModuleHeader.h"

using namespace ImpEngineModule;

class Trasform : public Component
{
public:
	Trasform(){}

	void Update(float dt) override 
	{
		std::cout << "Trasform Updated!\n";
	}

	float pos[3]{};
	float rot[3]{};
	float scale[3]{};
};

class GravitySystem : public System
{
public:
	void Update(World* world, float dt) override
	{
		world->Each<Trasform>([](Entity* ent, ComponentHandle<Trasform> transform)
			{
				std::cout << "Entity가 중력의 영향을 받는중 \n";
			}, false);
	}
};


int main()
{
	float dt = 1.f;
	World world;

	world.CreateEntity() ->AddComponent<Trasform>();
	Entity* ent = world.CreateEntity();
	world.Update(dt);

	GravitySystem system;

	world.RegisterSystem(&system);

	world.Update(dt);
	
	world.DestroyEntity(ent);


	return 0;
}