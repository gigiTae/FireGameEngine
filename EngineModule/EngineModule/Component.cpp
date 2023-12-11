#include "EngineModulePCH.h"
#include "Component.h"


ImpEngineModule::Component::Component()
	:_world(nullptr),_entity(nullptr),_isActive(false)
{}

ImpEngineModule::Component::~Component()
{

}

void ImpEngineModule::Component::Set(World* world, Entity* ent)
{
	_world = world;
	_entity = ent;
}
