#include "EngineModulePCH.h"
#include "Camera.h"
#include "World.h"
#include "InputManager.h"
#include "Transform.h"

#define IMP_EDITOR_MODE

ImpEngineModule::Camera::Camera()
{

}

ImpEngineModule::Camera::~Camera()
{

}

ImpEngineModule::Component* ImpEngineModule::Camera::Clone() const
{
	Camera* clone = new Camera();


	return clone;
}

void ImpEngineModule::Camera::Update(float dt)
{
}


void ImpEngineModule::Camera::OnMainCamera()
{
	World* world = GetWorld();

	/// 다른 메인 카메라가 있다면 끈다.
	world->Each<ImpEngineModule::Camera>([](Entity* ent, ComponentHandle<Camera> camera)
		{
			camera->OffMainCamera();
		}, false);

	_isMain = true;
}

void ImpEngineModule::Camera::Strafe(float distance)
{
	//mPosition = XMFLOAT3(mRight.x * d + mPosition.x, mRight.y * d + mPosition.y, mRight.z * d + mPosition.z);
	Transform* transform = GetComponent<Transform>();

	ImpMath::Vector3 position = transform->GetPosition();
	ImpMath::Vector3 rotation = transform->GetRotation();
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rotation);

	transform->SetPosition(ImpMath::Vector3(_rotMatrix._11 * distance + position.x,
		_rotMatrix._12 * distance + position.y, _rotMatrix._13 * distance + position.z));
}

void ImpEngineModule::Camera::Walk(float distance)
{
	//mPosition = XMFLOAT3(mLook.x * d + mPosition.x, mLook.y * d + mPosition.y, mLook.z * d + mPosition.z);
	Transform* transform = GetComponent<Transform>();

	ImpMath::Vector3 position = transform->GetPosition();
	ImpMath::Vector3 rotation = transform->GetRotation();
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rotation);

	transform->SetPosition(ImpMath::Vector3(_rotMatrix._31 * distance + position.x,
		_rotMatrix._32 * distance + position.y, _rotMatrix._33 * distance + position.z));
}

void ImpEngineModule::Camera::WorldUpDown(float distance)
{
	Transform* transform = GetComponent<Transform>();

	ImpMath::Vector3 position = transform->GetPosition();
	ImpMath::Vector3 rotation = transform->GetRotation();
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rotation);

	transform->SetPosition(ImpMath::Vector3(_rotMatrix._21 * distance + position.x,
		_rotMatrix._22 * distance + position.y, _rotMatrix._23 * distance + position.z));
}

void ImpEngineModule::Camera::Yaw(float angle)
{
	Transform* transform = GetComponent<Transform>();

	ImpMath::Vector3 rotation = transform->GetRotation();
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rotation);

	ImpMath::Vector3 up{ 0, 1, 0 };
	up = up.Normalize();

	rotation += up * angle;
	transform->SetRotation(rotation);
}

void ImpEngineModule::Camera::Pitch(float angle)
{
	Transform* transform = GetComponent<Transform>();

	ImpMath::Vector3 rotation = transform->GetRotation();
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rotation);

	ImpMath::Vector3 right{ 1, 0, 0 };
	right = right.Normalize();

	rotation += right * angle;
	transform->SetRotation(rotation);
}

void ImpEngineModule::Camera::Roll(float angle)
{
	Transform* transform = GetComponent<Transform>();

	ImpMath::Vector3 rotation = transform->GetRotation();
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rotation);

	ImpMath::Vector3 look{ 0, 0, 1 };
	look = look.Normalize();

	rotation += look * angle;
	transform->SetRotation(rotation);
}