#include "RendererPCH.h"
#include "Box.h"

Box::Box(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11RasterizerState* rs)
	:m_d3dDevice(device), m_d3dDeviceContext(deviceContext), m_rasterizerState(rs)
	, m_proj(), m_world(), m_view(), m_indexBuffer(), m_vertexBuffer(), m_inputLayout()
{}

Box::~Box()
{
	/// Conptr���
}

void Box::Initialize()
{
	BuildBuffers();
	BuildEffect();
	BuildLayout();
}

void Box::Update(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj)
{
	XMStoreFloat4x4(&m_world, world);
	XMStoreFloat4x4(&m_view, view);
	XMStoreFloat4x4(&m_proj, proj);
}

void Box::Render()
{
	// �Է� ��ġ ����
	m_d3dDeviceContext->IASetInputLayout(m_inputLayout.Get());
	m_d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_d3dDeviceContext->RSSetState(m_rasterizerState.Get());

	// ���ؽ� ���ۿ� �ε��� ���� ����
	UINT stride = sizeof(Box::Vertex);
	UINT offset = 0;

	m_d3dDeviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	m_d3dDeviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// ���
	XMMATRIX view = XMLoadFloat4x4(&m_view);
	XMMATRIX proj = XMLoadFloat4x4(&m_proj);
	XMMATRIX world = XMLoadFloat4x4(&m_world);
	XMMATRIX worldViewProj = world * view * proj;

	// ��� ���� ������ ���ؼ� ������������� ����� �������ش�.
	m_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	D3DX11_TECHNIQUE_DESC techDesc;
	m_tech->GetDesc(&techDesc);

	// �����н�?
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_tech->GetPassByIndex(p)->Apply(0, m_d3dDeviceContext.Get());
		m_d3dDeviceContext->DrawIndexed(indexSize, 0, 0);
	}

}

void Box::BuildBuffers()
{
	XMFLOAT4 green = XMFLOAT4(0.f, 1.f, 0.f, 1.f);

	Box::Vertex v[]{
		// ����
		XMFLOAT3(-1.f,-1.f,-1.f), green,
		XMFLOAT3(-1.f,1.f,-1.f), green,
		XMFLOAT3(1.f,-1.f,-1.f), green,
		XMFLOAT3(1.f,1.f,-1.f),green,
		// �ĸ�
		XMFLOAT3(-1.f,-1.f,1.f),green,
		XMFLOAT3(-1.f,1.f,1.f),green,
		XMFLOAT3(1.f,-1.f,1.f),green,
		XMFLOAT3(1.f,1.f,1.f),green };

	D3D11_BUFFER_DESC BF{};
	BF.ByteWidth = sizeof(Box::Vertex) * vertexSize; // ������ ���� ������ ũ��
	BF.Usage = D3D11_USAGE_DEFAULT;  // ���۰� ���̴� ��� 
	BF.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���� ����
	BF.CPUAccessFlags = 0;
	BF.MiscFlags = 0;
	BF.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA SD{};
	SD.pSysMem = &v;

	HR(m_d3dDevice->CreateBuffer(&BF, &SD, m_vertexBuffer.GetAddressOf()));

	UINT index[]{
		// ����
		0, 1, 2,  // �ﰢ�� 1	
		1, 3, 2,  // �ﰢ�� 2
		// �޸�
		 4, 5, 6,  // �ﰢ�� 3void Box::BuildFX()
		 5, 7, 6,  // �ﰢ�� 4{

		 // ���� ��}
		 0, 4, 2,  // �ﰢ�� 5
		 4, 6, 2,  // �ﰢ�� 6void Box::BuildLayout()

		 // ������ ��
		 1, 5, 3,  // �ﰢ�� 7}
		 5, 7, 3,  // �ﰢ�� 8

		 // ���� ��
		 1, 0, 5,  // �ﰢ�� 9
		 0, 4, 5,  // �ﰢ�� 10

		 // �Ʒ��� ��
		 2, 3, 6,  // �ﰢ�� 11
		 3, 7, 6   // �ﰢ�� 12
	};

	// ���� ���۸� �����ϴ� ����ü�� ä���.
	D3D11_BUFFER_DESC ibd{};
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * indexSize;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// ���� ���۸� �ʱ�ȭ�� �ڷḦ �����Ѵ�.
	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = &index;

	// ���� ���۸� �����Ѵ�.
	HR(m_d3dDevice->CreateBuffer(&ibd, &initData, m_indexBuffer.GetAddressOf()));
}

void Box::BuildEffect()
{
	std::ifstream fin("..\\Resource\\Shader\\color.cso", std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = static_cast<int>(fin.tellg());
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, m_d3dDevice.Get(), m_effect.GetAddressOf()));

	m_tech = m_effect->GetTechniqueByName("ColorTech");
	m_fxWorldViewProj = m_effect->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void Box::BuildLayout()
{
	// ��ǲ ���̾ƿ� ����
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	D3DX11_PASS_DESC passDesc;
	m_tech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(m_d3dDevice->CreateInputLayout(ied, 2, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, m_inputLayout.GetAddressOf()));

}
