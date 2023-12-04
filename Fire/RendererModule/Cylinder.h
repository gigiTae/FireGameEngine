#pragma once


/// <summary>
/// ���� �޽�
/// 
/// 
/// </summary>
class Cylinder
{
public:
	Cylinder(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11RasterizerState* rs);
	~Cylinder();

	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	void Initailize(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount);
	void Update(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj);
	void Render();

private:
	void BuildBuffers(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount);
	void BuildEffect();
	void BuildLayout();

	void BuildClinderBody(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount
						  , std::vector<Vertex>& vertices, std::vector<UINT>& indices);
	void BuildClinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount
							, std::vector<Vertex>& vertices, std::vector<UINT>& indices);
	void BuildClinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount
							   , std::vector<Vertex>& vertices, std::vector<UINT>& indices);

private:
	unsigned int vertexSize;
	unsigned int indexSize;

	float m_bottomRadius;
	float m_topRadius;
	float m_height;
	UINT m_sliceCount;
	UINT m_stackCount;

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

