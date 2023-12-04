#pragma once

namespace RendererModule
{
	/// <summary>
	/// ���� �⺻���� ���� 
	/// </summary>
	class BaseVertex
	{
	public:
		BaseVertex();
		BaseVertex(const XMFLOAT3& p, const XMFLOAT3& n, const XMFLOAT3& t, const XMFLOAT2& uv)
			: position(p), normal(n), tangent(t), uv(uv) {}
		BaseVertex(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u, float v)
			: position(px, py, pz), normal(nx, ny, nz),
			tangent(tx, ty, tz), uv(u, v) {}

		~BaseVertex();

		XMFLOAT3 position; // ��ġ��
		XMFLOAT3 normal;   // �ؽ��� ��ǥ
		XMFLOAT3 tangent;  // ź��Ʈ 
		DirectX::XMFLOAT2 uv;       // �븻
	};

	/// <summary>
	/// ��ġ, �÷��� �����ϴ� ����
	/// </summary>
	class SimpleVertex
	{
	public:
		SimpleVertex();
		~SimpleVertex();

		XMFLOAT3 position;
		XMFLOAT4 color;

	};



}