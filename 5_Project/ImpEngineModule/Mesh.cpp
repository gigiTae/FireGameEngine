#include "EngineModulePCH.h"
#include "Mesh.h"

ImpEngineModule::Mesh::Mesh()
{

}

ImpEngineModule::Mesh::~Mesh()
{

}

ImpEngineModule::Component* ImpEngineModule::Mesh::Clone() const
{
	Mesh* clone = new Mesh();

	clone->_texture = _texture;
	clone->_pixelShader = _pixelShader;
	clone->_vertexShader = _vertexShader;

	return clone;
}

void ImpEngineModule::Mesh::Start()
{

}

void ImpEngineModule::Mesh::Update(float dt)
{

}
