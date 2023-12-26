#include "pch.h"
#include "ImpGraphicsEngine.h"

#include "ImpD3D11Renderer.h"

ImpGraphics::ImpGraphicsEngine::ImpGraphicsEngine()
	:_renderer(nullptr)
{
	_renderer = new ImpGraphics::ImpD3D11Renderer;
}

ImpGraphics::ImpGraphicsEngine::~ImpGraphicsEngine()
{
	delete _renderer;
}

bool ImpGraphics::ImpGraphicsEngine::Initialize(int hinst, int hWnd, int screenWidth, int screenHeight)
{
	_renderer->Initialize(hinst, hWnd, screenWidth, screenHeight);

	return true;
}

void ImpGraphics::ImpGraphicsEngine::Update(float deltaTime)
{
	_renderer->Update(deltaTime);
}

void ImpGraphics::ImpGraphicsEngine::BeginRender()
{
	_renderer->BeginRender();
}

void ImpGraphics::ImpGraphicsEngine::Render(RendererType rendererType)
{
	// Todo: 아마도 달라질 부분
	_renderer->Render();
}

void ImpGraphics::ImpGraphicsEngine::EndRender()
{
	_renderer->EndRender();
}

void ImpGraphics::ImpGraphicsEngine::Finalize()
{
	_renderer->Finalize();
}

void ImpGraphics::ImpGraphicsEngine::SetClientSize(int width, int height)
{
	_renderer->SetClientSize(width, height);
}

void ImpGraphics::ImpGraphicsEngine::SetLight(LightInfo lightInfo)
{

}

void ImpGraphics::ImpGraphicsEngine::SetCamera(CameraInfo cameraInfo)
{
	_renderer->SetCamera(cameraInfo);
}

void ImpGraphics::ImpGraphicsEngine::SetMeshObject(MeshObjectInfo meshObjectInfo)
{

}

void* ImpGraphics::ImpGraphicsEngine::GetDevice()
{
	return _renderer->GetDevice();
}

void* ImpGraphics::ImpGraphicsEngine::GetDeviceContext()
{
	return _renderer->GetDeviceContext();
}
