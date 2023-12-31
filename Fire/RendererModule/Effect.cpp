#include "RendererPCH.h"
#include "Effect.h"
#include "Light.h"
#include "Material.h"


RendererModule::Effect::Effect(ID3D11Device* device, const std::wstring& fileName)
{
	/// 쉐이더 불러오기 
	std::ifstream fin(fileName, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, device, &m_fx));
}

RendererModule::Effect::~Effect()
{

}
