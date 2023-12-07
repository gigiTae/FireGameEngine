#include "EngineModulePCH.h"
#include "Component.h"

EngineModule::Component::Component(World* world, Entity* entity)
	:world(world),entity(entity),isActive(true)
{

}

EngineModule::Component::~Component()
{

}
