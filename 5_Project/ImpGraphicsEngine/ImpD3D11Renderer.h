#pragma once
#include "pch.h"
#include "IImp3DRenderer.h"

struct ID3DX11Effect;
struct ID3DX11EffectTechnique;
struct ID3DX11EffectMatrixVariable;

namespace ImpGraphics
{
	class ImpDevice;
	class ImpRenderTarget;
	class ImpRenderState;

	class ImpCamera;

	//temp
	class IObject;
	class Factory;
	class ResourceManager;

	class ImpD3D11Renderer : public IImp3DRenderer
	{
	public:
		ImpD3D11Renderer();
		virtual ~ImpD3D11Renderer();

		/// ���� �⺻������ �������� ���ư��� ���� �ʿ��� �ʼ� �Լ�
		// ���� ���۵�� ������� �ʾҴ�. 
		virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) override;
		virtual void Update(float deltaTime) override;
		virtual void BeginRender() override;
		virtual void Render() override;
		virtual void EndRender() override;
		virtual void Finalize() override;

		// â ��ȯ ����
		virtual void SetClientSize(int width, int height) override;

		virtual void SetLight(LightInfo lightInfo) override;
		virtual void SetCamera(CameraInfo cameraInfo) override;

		virtual void AddMeshObejct(MeshObjectInfo meshObjectInfo) override;
		virtual void SetMeshObject(size_t objectID, Matrix transformMatrix) override;
		virtual void DeleteMeshObject(size_t objectID) override;

		// temp
		virtual void* GetDevice() override;
		virtual void* GetDeviceContext() override;

	private:
		/// window(screen) ����
		// �����찡 ���� ���� ���� ������
		HWND _hWnd;
		
		UINT _screenWidth;
		UINT _screenHeight;

		ImpDevice* _device;
		ImpRenderTarget* _renderTarget;
		ImpRenderState* _renderState;

		ImpCamera* _camera;

		std::unordered_map<size_t, IObject*> _objects;
		//temp
		IObject* _object;
		Factory* _factory;
		ResourceManager* _resourceManager;
	};
}