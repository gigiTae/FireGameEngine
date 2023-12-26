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

		/// 기본 인터페이스
		virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) override;
		virtual void Update(float deltaTime) override;
		virtual void BeginRender() override;
		virtual void Render(RendererType rendererType) override;
		virtual void EndRender() override;
		virtual void Finalize() override;

		/// 창 크기 변환
		virtual void SetClientSize(int width, int height) override;

		/// 그리기 위해 필요한 오브젝트들
		virtual void SetLight(LightInfo lightInfo) override;
		virtual void SetCamera(CameraInfo cameraInfo) override;
		virtual void SetMeshObject(MeshObjectInfo meshObjectInfo) override;

		// temp 
		/// IMGUI를 위해서 필요한 Device, DeviceContext 반환
		// 여기에 ID3D11Device를 써버리면 아마도 게임엔진에서
		// D3D를 include 해야할 것 같다. 그렇다고 void* 가 맞는걸까?
		virtual void* GetDevice() override;
		virtual void* GetDeviceContext() override;

	private:
		IImp3DRenderer* _renderer;
	};
}

