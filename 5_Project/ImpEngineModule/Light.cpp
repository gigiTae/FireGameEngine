#include "EngineModulePCH.h"
#include "Light.h"

ImpEngineModule::Light::Light()
	:_type(LightType::Point),_intensity(0.f)
{

}

ImpEngineModule::Light::~Light()
{

}

ImpEngineModule::Component* ImpEngineModule::Light::Clone() const
{
	Light* clone = new Light();

	clone->_intensity = _intensity;
	clone->_type = _type;

	return clone;
}

void ImpEngineModule::Light::Update(float dt)
{

}
