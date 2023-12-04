#pragma once

/// <summary>
/// ������ 
/// 
/// ������ ���� ���̰� ���� ���̵� ���� �ﰢ����� ���� �ٻ��Ѵ�.
/// 
/// </summary>
class GeoSphere
{
public:
	GeoSphere(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11RasterizerState* rs);
	~GeoSphere();

	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT3 tangentU;
		XMFLOAT2 texC;
	};
	
public:
	void Initilize(float radius, UINT numSubdivisions);
	void Update(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj);
	void Render();

private:
	void BulidBuffers(float radius, UINT numSubdivisions);
	void BuildEffect();
	void BuildLayout();

	void SubDivide(std::vector<Vertex>& vertices, std::vector<UINT>& indices);

private:
	UINT m_vertexSize;
	UINT m_indexSize;
	UINT m_numSubdivisions;
	float m_radius;

	XMFLOAT4X4 m_world; // ���� ��ȯ ���
	XMFLOAT4X4 m_view;  // �þ� ��ȯ ���
	XMFLOAT4X4 m_proj;  // ���� ��ȯ ��� 

	ComPtr<ID3D11Device> m_d3dDevice;
	ComPtr<ID3D11DeviceContext> m_d3dDeviceContext;

	/// ======================== �ڿ� =============================
	ComPtr<ID3D11Buffer>  m_vertexBuffer;
	ComPtr<ID3D11Buffer>  m_indexBuffer;
	ComPtr<ID3D11InputLayout> m_inputLayout;
	ComPtr<ID3D11RasterizerState> m_rasterizerState;

	ComPtr<ID3DX11Effect> m_effect;	// ����Ʈ
	ComPtr<ID3DX11EffectTechnique> m_tech;	// ��ũ
	ComPtr<ID3DX11EffectMatrixVariable> m_fxWorldViewProj;	// ����Ʈ�뺯��

};

