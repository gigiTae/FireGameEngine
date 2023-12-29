#include "pch.h"
#include "ImpD3D11Renderer.h"

#include "Define.h"

#include "ImpDevice.h"
#include "ImpRenderTarget.h"
#include "ImpRenderState.h"

#include "ImpCamera.h"

//temp
#include <DirectXColors.h>

#include "IObject.h"
#include "MeshObject.h"
#include "Factory.h"
#include "ResourceManager.h"
#include "BuildInfo.h"

using namespace ImpGraphics;

// temp
using namespace DirectX;

ImpD3D11Renderer::ImpD3D11Renderer()
	: _hWnd(0),
	_screenWidth(0), _screenHeight(0),
	_device(nullptr), _renderTarget(nullptr),
	_camera(nullptr), _object(nullptr),
	_factory(nullptr), _resourceManager(nullptr),
	_quadObjectForDeferred(nullptr)
{
	_device = new ImpDevice;
	_renderTarget = new ImpRenderTarget(_device);
	_renderState = new ImpRenderState;
}

ImpD3D11Renderer::~ImpD3D11Renderer()
{
	delete _resourceManager;
	delete _factory;
	delete _object;

	delete _camera;

	delete _renderState;
	delete _renderTarget;
	delete _device;
}

bool ImpD3D11Renderer::Initialize(int hinst, int hWnd, int screenWidth, int screenHeight)
{
#pragma warning(disable : 4312)
	_hWnd = reinterpret_cast<HWND>(hWnd);
#pragma warning(default : 4312)
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_device->Initialize(hWnd, screenWidth, screenHeight);
	_renderTarget->Initialize(screenWidth, screenHeight);
	_renderState->Initialize(_device->GetDevice());

	_camera = new ImpCamera(screenWidth, screenHeight);

	// temp
	_resourceManager = new ResourceManager(_device);
	_factory = new Factory(_resourceManager);

	//_object = _factory->CreateObject(ObjectType::MeshObject, L"NULL", L"../ImpGraphicsEngine/ColorVS.hlsl", L"../ImpGraphicsEngine/ColorPS.hlsl");
	//_object = _factory->CreateObject(ObjectType::MeshObject, L"Resources/Imp/Box.imp", L"../ImpGraphicsEngine/FirstPassVS.hlsl", L"../ImpGraphicsEngine/FirstPassPS.hlsl");
	_object = _factory->CreateObject(ObjectType::MeshObject, L"Resources/Imp/dd.fbx", L"../ImpGraphicsEngine/FirstNormalVS.hlsl", L"../ImpGraphicsEngine/FirstNormalPS.hlsl");
	_quadObjectForDeferred = _factory->CreateObject(ObjectType::QuadObject, L"Resources/Imp/Quad.imp", L"../ImpGraphicsEngine/SecondPassVS.hlsl", L"../ImpGraphicsEngine/SecondPassPS.hlsl");

 	return true;
}

void ImpD3D11Renderer::Update(float deltaTime)
{
	//temp
	Matrix temp = Matrix::Identity();
	DirectX::XMMATRIX xmTransformMatrix(&temp._11);
	_object->SetTransformMatrix(xmTransformMatrix);
	_object->Update(_camera);
	for (const auto& object : _objects)
	{
		object.second->Update(_camera);
	}
}

void ImpD3D11Renderer::BeginRender()
{
	ID3D11DeviceContext* deviceContext = _device->GetDeviceContext();
	assert(deviceContext);

	_renderTarget->FirstPassBind();
	_renderTarget->FirstPassClear();
}

void ImpD3D11Renderer::Render()
{
	for (const auto& object : _objects)
	{
		object.second->Render(_device, _renderState, _renderTarget);
	}
	//_object->Render(_device, _renderState, _renderTarget);
	_quadObjectForDeferred->Render(_device, _renderState, _renderTarget);
}

void ImpD3D11Renderer::EndRender()
{
	IDXGISwapChain* swapChain = _device->GetSwapChain();
	assert(swapChain);

	HR(swapChain->Present(0, 0));
}

void ImpD3D11Renderer::Finalize()
{

}

void ImpD3D11Renderer::SetClientSize(int width, int height)
{
	_screenWidth = width;
	_screenHeight = height;

	_renderTarget->OnResize(width, height);
	_camera->SetScreenSize(width, height);
}

void* ImpD3D11Renderer::GetDevice()
{
	return _device->GetDevice();
}

void* ImpD3D11Renderer::GetDeviceContext()
{
	return _device->GetDeviceContext();
}

void ImpD3D11Renderer::SetLight(LightInfo lightInfo)
{

}

void ImpD3D11Renderer::SetCamera(CameraInfo cameraInfo)
{
	_camera->Update(cameraInfo);
}

void ImpD3D11Renderer::SetMeshObject(size_t objectID, Matrix transformMatrix)
{
	DirectX::XMMATRIX xmTransformMatrix(&transformMatrix._11);
	_objects[objectID]->SetTransformMatrix(xmTransformMatrix);

}

void ImpD3D11Renderer::AddMeshObejct(MeshObjectInfo meshObjectInfo)
{
	IObject* temp = _factory->CreateObject(
		ObjectType::MeshObject, meshObjectInfo._meshPath, meshObjectInfo._vertexShaderPath, meshObjectInfo._pisxelShaderPath);

	_objects[meshObjectInfo._objectID] = temp;
}

void ImpD3D11Renderer::DeleteMeshObject(size_t objectID)
{
	IObject* temp = _objects[objectID];
	if (temp != nullptr)
	{
		delete temp;
	}

	_objects.erase(objectID);
}