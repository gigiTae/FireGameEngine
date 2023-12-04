#pragma once

namespace RendererModule
{

	/// <summary>
	/// ���� �Է� ���� ���� Ŭ����
	/// 
	/// InputLayout�� Ŭ����ȭ �غ���
	/// 
	/// </summary>
	class InputLayout
	{
	public:
		InputLayout();
		~InputLayout();

		void Initailize(ID3D11Device* device);
		void Finalize();

	public:
		ID3D11InputLayout* GetSimpleLayout() const { return m_simple.Get(); }
		ID3D11InputLayout* GetBasicLayout() const { return m_basic.Get(); }

	private:
		ComPtr<ID3D11Device> m_d3dDevice;

		ComPtr<ID3D11InputLayout> m_basic;
		D3D11_INPUT_ELEMENT_DESC m_basicDesc[3];

		ComPtr<ID3D11InputLayout> m_simple;
		D3D11_INPUT_ELEMENT_DESC m_simpleDesc[2];
	};

}