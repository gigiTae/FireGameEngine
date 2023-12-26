#pragma once
#include "IImpGraphicsEngine.h"

namespace ImpGraphics
{
	class ImpCamera
	{
	public:
		ImpCamera(int width, int height);
		~ImpCamera(); // 만약 인터페이스를 따로 만들거나 하려면 가상소멸자로

		void Update(const CameraInfo& cameraInfo);

		void MakeViewTM(const CameraInfo& cameraInfo);
		DirectX::XMFLOAT4X4 GetViewTM();

		void MakePerspectiveProjTM(const CameraInfo& cameraInfo);
		void MakeOthographicProjTM(const CameraInfo& cameraInfo);
		DirectX::XMFLOAT4X4 GetProjTM();

		void SetScreen(int width, int height);

	private:
		int _screenWidth;
		int _screenHeight;

		DirectX::XMFLOAT4X4 _viewTM;
		DirectX::XMFLOAT4X4 _projTM;
	};
}

/// 기존 3Q 과제에서 쓰던 카메라 인터페이스

/*
/// <summary>
/// 카메라 클래스 추상화
///
/// 2021.03.17 LeHideKGIT
/// </summary>
class IDRCamera abstract
{
public:
	// Strafe/Walk the camera a distance d.
	virtual void Strafe(float d) = 0;
	virtual void Walk(float d) = 0;
	virtual void WorldUpDown(float d) = 0;

	// Rotate the camera.
	virtual void Pitch(float angle) = 0;
	virtual void RotateY(float angle) = 0;

	// After modifying camera position/orientation, call to rebuild the view matrix.
	virtual void UpdateViewMatrix() = 0;

	// Get View/Proj matrices.
	///virtual XMMATRIX View() const = 0;
	///virtual XMMATRIX Proj() const = 0;
	///virtual XMMATRIX ViewProj() const = 0;

	// Set frustum.
	virtual void SetLens(float fovY, float aspect, float zn, float zf) = 0;
};*/

/*
#pragma once

#include "DX11Define.h"

/// <summary>
/// 카메라 클래스. DX11 종속적
/// </summary>
class DRCamera
{
public:
	DRCamera();
	~DRCamera();

	// Get/Set world camera position.
	XMVECTOR GetPositionXM() const;
	XMFLOAT3 GetPosition() const;
	void SetPosition(float x, float y, float z);
	void SetPosition(const XMFLOAT3& v);

	// Get camera basis vectors.
	XMVECTOR GetRightXM() const;
	XMFLOAT3 GetRight() const;
	XMVECTOR GetUpXM() const;
	XMFLOAT3 GetUp() const;
	XMVECTOR GetLookXM() const;
	XMFLOAT3 GetLook() const;

	// Get frustum properties.
	float GetNearZ() const;
	float GetFarZ() const;
	float GetAspect() const;
	float GetFovY() const;
	float GetFovX() const;

	// Get near and far plane dimensions in view space coordinates.
	float GetNearWindowWidth() const;
	float GetNearWindowHeight() const;
	float GetFarWindowWidth() const;
	float GetFarWindowHeight() const;

	// Set frustum.
	void SetLens(float fovY, float aspect, float zn, float zf);

	// Define camera space via LookAt parameters.
	void LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);
	void LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);

	// Get View/Proj matrices.
	XMMATRIX View() const;
	XMMATRIX Proj() const;
	XMMATRIX ViewProj() const;

	// Strafe/Walk the camera a distance d.
	void Strafe(float d);
	void Walk(float d);
	void WorldUpDown(float d);

	// Rotate the camera.
	void Pitch(float angle);
	void RotateY(float angle);

	// After modifying camera position/orientation, call to rebuild the view matrix.
	void UpdateViewMatrix();
private:
	// Camera coordinate system with coordinates relative to world space.
	XMFLOAT3 mPosition;
	XMFLOAT3 mRight;
	XMFLOAT3 mUp;
	XMFLOAT3 mLook;

	// Cache frustum properties.
	float mNearZ;
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	// Cache View/Proj matrices.
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
};*/

/*
#include "DRCamera.h"


DRCamera::DRCamera()
	: mPosition(0.0f, 0.0f, 0.0f),
	mRight(1.0f, 0.0f, 0.0f),
	mUp(0.0f, 1.0f, 0.0f),
	mLook(0.0f, 0.0f, 1.0f)
{
	//SetLens(0.25f * MathHelper::Pi, 1.0f, 0.0001f, 1000.0f);
}

DRCamera::~DRCamera()
{

}

XMVECTOR DRCamera::GetPositionXM() const
{
	return XMLoadFloat3(&mPosition);
}

XMFLOAT3 DRCamera::GetPosition() const
{
	return mPosition;
}

void DRCamera::SetPosition(float x, float y, float z)
{
	mPosition = XMFLOAT3(x, y, z);
}

void DRCamera::SetPosition(const XMFLOAT3& v)
{
	mPosition = v;
}

XMVECTOR DRCamera::GetRightXM() const
{
	return XMLoadFloat3(&mRight);
}

XMFLOAT3 DRCamera::GetRight() const
{
	return mRight;
}

XMVECTOR DRCamera::GetUpXM() const
{
	return XMLoadFloat3(&mUp);
}

XMFLOAT3 DRCamera::GetUp() const
{
	return mUp;
}

XMVECTOR DRCamera::GetLookXM() const
{
	return XMLoadFloat3(&mLook);
}

XMFLOAT3 DRCamera::GetLook() const
{
	return mLook;
}

float DRCamera::GetNearZ() const
{
	return mNearZ;
}

float DRCamera::GetFarZ() const
{
	return mFarZ;
}

float DRCamera::GetAspect() const
{
	return mAspect;
}

float DRCamera::GetFovY() const
{
	return mFovY;
}

float DRCamera::GetFovX() const
{
	float halfWidth = 0.5f * GetNearWindowWidth();
	return 2.0f * atan(halfWidth / mNearZ);
}

float DRCamera::GetNearWindowWidth() const
{
	return mAspect * mNearWindowHeight;
}

float DRCamera::GetNearWindowHeight() const
{
	return mNearWindowHeight;
}

float DRCamera::GetFarWindowWidth() const
{
	return mAspect * mFarWindowHeight;
}

float DRCamera::GetFarWindowHeight() const
{
	return mFarWindowHeight;
}

void DRCamera::SetLens(float fovY, float aspect, float zn, float zf)
{
	// cache properties
	mFovY = fovY;
	mAspect = aspect;
	mNearZ = zn;
	mFarZ = zf;

	mNearWindowHeight = 2.0f * mNearZ * tanf(0.5f * mFovY);
	mFarWindowHeight = 2.0f * mFarZ * tanf(0.5f * mFovY);

	XMMATRIX P = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
	XMStoreFloat4x4(&mProj, P);
}

void DRCamera::LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
{
	// 시선벡터와 월드업을 외적하면 right벡터가 나오고
	// 다시 그 right벡터와 시선벡터를 외적하면 내 up벡터가 나옴
	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(target, pos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&mPosition, pos);
	XMStoreFloat3(&mLook, L);
	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
}

void DRCamera::LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up)
{
	XMVECTOR P = XMLoadFloat3(&pos);
	XMVECTOR T = XMLoadFloat3(&target);
	XMVECTOR U = XMLoadFloat3(&up);

	LookAt(P, T, U);
}

XMMATRIX DRCamera::View() const
{
	return XMLoadFloat4x4(&mView);
}

XMMATRIX DRCamera::Proj() const
{
	return XMLoadFloat4x4(&mProj);
}

XMMATRIX DRCamera::ViewProj() const
{
	return XMMatrixMultiply(View(), Proj());
}

void DRCamera::Strafe(float d)
{
	// mPosition += d*mRight
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat3(&mRight);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, r, p));
}

void DRCamera::Walk(float d)
{
	// mPosition += d*mLook
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR l = XMLoadFloat3(&mLook);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, l, p));
}

void DRCamera::WorldUpDown(float d)
{
	// mPosition += d * mUp
	XMVECTOR scale = XMVectorReplicate(d);
	XMVECTOR up = XMLoadFloat3(&mUp);
	XMVECTOR position = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(scale, up, position));
}

void DRCamera::Pitch(float angle)
{
	// Rotate up and look vector about the right vector.

	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&mRight), angle);

	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void DRCamera::RotateY(float angle)
{
	// Rotate the basis vectors about the world y-axis.

	XMMATRIX R = XMMatrixRotationY(angle);

	XMStoreFloat3(&mRight, XMVector3TransformNormal(XMLoadFloat3(&mRight), R));
	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void DRCamera::UpdateViewMatrix()
{
	XMVECTOR R = XMLoadFloat3(&mRight);
	XMVECTOR U = XMLoadFloat3(&mUp);
	XMVECTOR L = XMLoadFloat3(&mLook);
	XMVECTOR P = XMLoadFloat3(&mPosition);

	// Keep camera's axes orthogonal to each other and of unit length.
	L = XMVector3Normalize(L);
	U = XMVector3Normalize(XMVector3Cross(L, R));

	// U, L already ortho-normal, so no need to normalize cross product.
	R = XMVector3Cross(U, L);

	// Fill in the view matrix entries.
	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));

	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
	XMStoreFloat3(&mLook, L);

	mView(0, 0) = mRight.x;
	mView(1, 0) = mRight.y;
	mView(2, 0) = mRight.z;
	mView(3, 0) = x;

	mView(0, 1) = mUp.x;
	mView(1, 1) = mUp.y;
	mView(2, 1) = mUp.z;
	mView(3, 1) = y;

	mView(0, 2) = mLook.x;
	mView(1, 2) = mLook.y;
	mView(2, 2) = mLook.z;
	mView(3, 2) = z;

	mView(0, 3) = 0.0f;
	mView(1, 3) = 0.0f;
	mView(2, 3) = 0.0f;
	mView(3, 3) = 1.0f;
}*/