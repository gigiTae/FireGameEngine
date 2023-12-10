#pragma once

namespace RendererModule
{
	/// <summary>
	/// ����������������
	/// �������� �ʿ��� �������� �Ѵ�.
	/// </summary>
	class RenderingPipeline
	{
	public:
		RenderingPipeline(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~RenderingPipeline();

		/// �ʿ��� �������� �����غ���

		/// 1. ��������
		/// 2. �ε��� ����
		/// 4. InputLayout
		/// 5. Effect
		/// 6. ��ȯ ���
	
		/// 3. RasterizerState

	private:
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
	};
}

