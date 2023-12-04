#pragma once

namespace RendererModule
{

	// ������ Ư���� ���Ѵ� 
class Material
{
public:
	Material();
	~Material();

	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
	XMFLOAT4 specular;
	XMFLOAT4 reflect;
};


}