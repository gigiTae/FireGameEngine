#include "EngineModulePCH.h"
#include "Mesh.h"

ImpEngineModule::Mesh::Mesh()
	:_isBindGraphics(false)
{

}

ImpEngineModule::Mesh::~Mesh()
{

}

ImpEngineModule::Component* ImpEngineModule::Mesh::Clone() const
{
	Mesh* clone = new Mesh();

	clone->_fbx = _fbx;
	clone->_pixelShader = _pixelShader;
	clone->_vertexShader = _vertexShader;
	clone->_isBindGraphics = false;

	return clone;
}

void ImpEngineModule::Mesh::Start()
{

}

void ImpEngineModule::Mesh::Update(float dt)
{

}
