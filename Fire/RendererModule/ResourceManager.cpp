#include "RendererPCH.h"
#include "ResourceManager.h"
#include "FileLoader.h"
#include "Effect.h"
#include "BasicEffect.h"


RendererModule::ResourceManager::ResourceManager()
	:m_d3dDevice()
	,m_shaderResourceViewMap{}
{

}

RendererModule::ResourceManager::~ResourceManager()
{

}

void RendererModule::ResourceManager::Initialize(ID3D11Device* device)
{
	m_d3dDevice = device;


	/// �ؽ�ó �ε� 
	LoadTextures();

	/// ����Ʈ �ε�
	LoadEffect();
}

ID3D11ShaderResourceView* RendererModule::ResourceManager::GetShaderResourceView(const std::wstring& fileName)
{
	auto iter = m_shaderResourceViewMap.find(fileName);

	assert(iter != m_shaderResourceViewMap.end() || L"ã�� ���ҽ��� �����ϴ�.");

	return iter->second.Get();
}

RendererModule::Effect* RendererModule::ResourceManager::GetEffect(const std::wstring& effectKey)
{
	auto iter = m_effects.find(effectKey);
	assert(iter != m_effects.end());

	return iter->second.get();
}

void RendererModule::ResourceManager::LoadTextures()
{
	// �ؽ�ó ���ϰ�� �ҷ����� 
	const std::wstring& filePath = RendererModule::File::GetCurrentFilePath();
	std::wstring texturePath = filePath + L"Resource\\Texture";

	std::vector<std::wstring> textureFileMember{};

	File::GetFileMemberPath(textureFileMember, texturePath, true);

	for (const auto& path : textureFileMember)
	{
		CreateShaderResourceView(path);
	}

}

void RendererModule::ResourceManager::LoadEffect()
{
	/// ����Ʈ�� ���� 
	Effect* basicFX = new BasicEffect(m_d3dDevice.Get(), L"..\\Resource\\Shader\\Basic.cso");
	m_effects.insert(std::make_pair(L"Basic", basicFX));

}

void RendererModule::ResourceManager::CreateShaderResourceView(const std::wstring& filePath)
{
	using std::wstring;

	wstring fileName = File::GetFileName(filePath); // fileName => key

	auto iter = m_shaderResourceViewMap.find(fileName);
	assert(iter == m_shaderResourceViewMap.end() || !L"�ߺ� Ű���Դϴ�.");

	wstring extension = File::GetFileExtension(filePath);

	DirectX::ScratchImage image;

	HRESULT hr = S_OK;

	if (extension == L"tga" || extension == L"targa")
	{
		hr = LoadFromTGAFile(filePath.c_str(), nullptr, image);
	}
	else
	{
		hr = LoadFromWICFile(filePath.c_str(), WIC_FLAGS_NONE, nullptr, image);
	}

	assert(hr == S_OK || !L"���Ϸε� ����");

	ID3D11Texture2D* texture = nullptr;
	HR(CreateTexture(m_d3dDevice.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(),
		reinterpret_cast<ID3D11Resource**>(&texture)));

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Format = image.GetMetadata().format;

	ID3D11ShaderResourceView* shaderResourceView = nullptr;
	HR(m_d3dDevice->CreateShaderResourceView(texture, &srvDesc, &shaderResourceView));

	texture->Release();

	m_shaderResourceViewMap.insert(std::make_pair(fileName, shaderResourceView));
}
