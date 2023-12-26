#pragma once
#include "IImpGraphicsEngine.h"

namespace ImpGraphics 
{
	class IImp3DRenderer;

	class ImpGraphicsEngine : public IImpGraphicsEngine
	{
	public:
		ImpGraphicsEngine();
		virtual ~ImpGraphicsEngine();

		/// �⺻ �������̽�
		virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) override;
		virtual void Update(float deltaTime) override;
		virtual void BeginRender() override;
		virtual void Render(RendererType rendererType) override;
		virtual void EndRender() override;
		virtual void Finalize() override;

		/// â ũ�� ��ȯ
		virtual void SetClientSize(int width, int height) override;

		/// �׸��� ���� �ʿ��� ������Ʈ��
		virtual void SetLight(LightInfo lightInfo) override;
		virtual void SetCamera(CameraInfo cameraInfo) override;
		virtual void SetMeshObject(MeshObjectInfo meshObjectInfo) override;

		// temp 
		/// IMGUI�� ���ؼ� �ʿ��� Device, DeviceContext ��ȯ
		// ���⿡ ID3D11Device�� ������� �Ƹ��� ���ӿ�������
		// D3D�� include �ؾ��� �� ����. �׷��ٰ� void* �� �´°ɱ�?
		virtual void* GetDevice() override;
		virtual void* GetDeviceContext() override;

	private:
		IImp3DRenderer* _renderer;
	};
}

