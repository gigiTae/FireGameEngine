#include "EngineModulePCH.h"
#include "Component.h"


ImpEngineModule::Component::Component()
	:m_world(nullptr),m_entity(nullptr),m_isActive(false)
{}

ImpEngineModule::Component::~Component()
{

}

void ImpEngineModule::Component::Set(World* world, Entity* ent)
{
	m_world = world;
	m_entity = ent;
}
