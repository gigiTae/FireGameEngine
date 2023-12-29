#include "pch.h"
#include "ImpCamera.h"

using namespace DirectX;

ImpGraphics::ImpCamera::ImpCamera(int screenWidth, int screenHeight)
	:_screenWidth(screenWidth),
	_screenHeight(screenHeight),
	_viewTM(), _projTM()
{
}

ImpGraphics::ImpCamera::~ImpCamera()
{

}

void ImpGraphics::ImpCamera::Update(const CameraInfo& cameraInfo)
{
	MakeViewTM(cameraInfo);
	if (cameraInfo._isPerspective)
	{
		MakePerspectiveProjTM(cameraInfo);
	}
	else
	{
		MakeOthographicProjTM(cameraInfo);
	}
}

void ImpGraphics::ImpCamera::MakeViewTM(const CameraInfo& cameraInfo)
{
	// 雀傈 青纺 积己
	float pitch = XMConvertToRadians(cameraInfo._rotation.x);
	float yaw = XMConvertToRadians(cameraInfo._rotation.y);
	float roll = XMConvertToRadians(cameraInfo._rotation.z);

	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// 捞悼 青纺 积己
	XMMATRIX translationMatrix = 
		XMMatrixTranslation(cameraInfo._position.x, cameraInfo._position.y, cameraInfo._position.z);

	//XMMATRIX viewTM = translationMatrix * rotationMatrix;
	XMMATRIX viewTM = rotationMatrix * translationMatrix;
	XMStoreFloat4x4(&_viewTM, XMMatrixInverse(nullptr, viewTM));
}

void ImpGraphics::ImpCamera::MakePerspectiveProjTM(const CameraInfo& cameraInfo)
{
	DirectX::XMMATRIX PerspecProjTM = DirectX::XMMatrixPerspectiveFovLH(cameraInfo._fieldOfView, static_cast<float>(_screenWidth) / _screenHeight, cameraInfo._nearPlain, cameraInfo._farPlain);
	XMStoreFloat4x4(&_projTM, PerspecProjTM);
}

void ImpGraphics::ImpCamera::MakeOthographicProjTM(const CameraInfo& cameraInfo)
{
	DirectX::XMMATRIX othoProjTM = DirectX::XMMatrixOrthographicLH(static_cast<float>(_screenWidth), static_cast<float>(_screenWidth), cameraInfo._nearPlain, cameraInfo._farPlain);
	XMStoreFloat4x4(&_projTM, othoProjTM);
}

DirectX::XMFLOAT4X4 ImpGraphics::ImpCamera::GetViewTM()
{
	return _viewTM;
}

DirectX::XMFLOAT4X4 ImpGraphics::ImpCamera::GetProjTM()
{
	return _projTM;
}

void ImpGraphics::ImpCamera::SetScreenSize(int width, int height)
{
	_screenWidth = width;
	_screenHeight = height;
}