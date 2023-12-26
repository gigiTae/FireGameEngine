#include "pch.h"
#include "ImpDevice.h"

#include "Define.h"

using namespace ImpGraphics;

ImpDevice::ImpDevice()
	:_device(nullptr),
	_deviceContext(nullptr),
	_swapChain(nullptr)
{

}

ImpDevice::~ImpDevice()
{
	// ������ ������ ����
	ReleaseCOM(_swapChain);

	// Restore all default settings.
	if (_deviceContext)
	{
		_deviceContext->ClearState();
	}

	ReleaseCOM(_deviceContext);
	ReleaseCOM(_device);
}

bool ImpDevice::Initialize(int hWnd, int screenWidth, int screenHeight)
{
	// ����̽� ���� ���. ����� ������ ��� ����� ����
	UINT _createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	_createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// ����̹� Ÿ��
	D3D_DRIVER_TYPE driveType = D3D_DRIVER_TYPE_HARDWARE;

	// ����ü�� ����
	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.Width = screenWidth;
	sd.BufferDesc.Height = screenHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = (HWND)hWnd;		// DXGI-Windef
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	sd.SampleDesc.Count = 1;			// No MSAA
	sd.SampleDesc.Quality = 0;

	D3D_FEATURE_LEVEL featureLevel;

	/// 1. ����̽��� ����̽����ؽ�Ʈ�� ����ü���� �� �濡 �����Ѵ�.
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		0, driveType, 0, _createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &sd,
		&_swapChain, &_device, &featureLevel, &_deviceContext);

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	return true;
}

/*
bool ImpD3D11Renderer::Initialize(int hinst, int hWnd, int screenWidth, int screenHeight)
{
#pragma warning(disable : 4312)
	_hWnd = reinterpret_cast<HWND>(hWnd);
#pragma warning(default : 4312)
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	/// ����� ������ ��� DX11 ����� ���

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	/// D3����̽��� ����̽� ���ؽ�Ʈ�� �����Ѵ�.

	// ���� ����
	D3D_FEATURE_LEVEL featureLevel;
	featureLevel = D3D_FEATURE_LEVEL_1_0_CORE;
	HRESULT hr = D3D11CreateDevice(
		0,                 // default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0,                 // no software device
		createDeviceFlags,
		0, 0,              // default feature level array
		D3D11_SDK_VERSION,
		&_d3dDevice,
		&featureLevel,
		&_d3dDeviceContext);

	/// ��Ƽ���ø� ��ܰ���� �Ǵ��� üũ
	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render
	// target formats, so we only need to check quality support.

	HR(_d3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQuality));
	assert(_4xMsaaQuality > 0);

	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.Width = _screenWidth;
	sd.BufferDesc.Height = _screenHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Use 4X MSAA?
	if (_enable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = _4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = _hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	// To correctly create the swap chain, we must use the IDXGIFactory that was
	// used to create the device.  If we tried to use a different IDXGIFactory instance
	// (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain:
	// This function is being called with a device from a different IDXGIFactory."

	// D3����̽��κ��� dxgi����̽��� ���´�.
	IDXGIDevice* dxgiDevice = nullptr;
	HR(_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	// dxgi����̽��κ��� dxgi����͸� ���´�.
	IDXGIAdapter* dxgiAdapter = nullptr;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	// dxgi����ͷκ��� dxgi���丮�� ���´�.
	IDXGIFactory* dxgiFactory = nullptr;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	// ���� ����ü���� �����Ѵ�.
	if (_d3dDevice == nullptr)
	{
		MessageBox(NULL, L"D3DDevice�� nullptr�Դϴ�.", L"����", MB_ICONERROR);
	}
	else
	{
		HR(dxgiFactory->CreateSwapChain(_d3dDevice, &sd, &_d3dSwapChine));
	}

	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);

	OnResize();

	return true;
}
*/