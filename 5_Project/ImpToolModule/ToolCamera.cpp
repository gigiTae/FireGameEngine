#include "ImpToolModulePCH.h"
#include "ToolCamera.h"


ImpToolModule::ToolCamera::ToolCamera()
{

}

ImpToolModule::ToolCamera::~ToolCamera()
{

}


void ImpToolModule::ToolCamera::Initialize(ImpEngineModule::EngineModule* engineModule)
{
	_engineModule = engineModule;

	_ent = std::make_unique<ImpEngineModule::Entity>();

	_ent->AddComponent<ImpEngineModule::Transform>();
	_ent->AddComponent<ImpEngineModule::Camera>();
}

void ImpToolModule::ToolCamera::Update()
{
	using namespace ImpEngineModule;

	auto input = _engineModule->GetInputManager();

	// Transform ��������  
	Transform* transform = _ent->GetComponent<Transform>();
	Camera* camera = _ent->GetComponent<Camera>();
	/// Ű�Է� -> ī�޶� �̵�
	const float speed = 0.01f;

	if (input->IsKeyState(KEY::RMOUSE, KEY_STATE::HOLD))
	{
		if (input->IsKeyState(KEY::A, KEY_STATE::HOLD))
		{
			camera->Strafe(-speed);
		}
		if (input->IsKeyState(KEY::D, KEY_STATE::HOLD))
		{
			camera->Strafe(speed);
		}
		if (input->IsKeyState(KEY::W, KEY_STATE::HOLD))
		{
			camera->Walk(speed);
		}
		if (input->IsKeyState(KEY::S, KEY_STATE::HOLD))
		{
			camera->Walk(-speed);
		}
		if (input->IsKeyState(KEY::Q, KEY_STATE::HOLD))
		{
			camera->WorldUpDown(-speed);
		}
		if (input->IsKeyState(KEY::E, KEY_STATE::HOLD))
		{
			camera->WorldUpDown(speed);
		}
	}

	/// Ű�Է� -> ī�޶� ȸ��
	if (input->IsKeyState(KEY::RMOUSE, KEY_STATE::HOLD))
	{
		//float dx = XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
		//radian = degree * (pi / 180)
		float dx = (0.15f * static_cast<float>(input->GetDeltaMousePosition().x)/* * (3.141592 / 180)*/);
		float dy = (0.15f * static_cast<float>(input->GetDeltaMousePosition().y)/* * (3.141592 / 180)*/);

		camera->Pitch(dy);
		camera->Yaw(dx);
	}
	/// Roll�� �ϴ� �Ⱦ�!
// 		if (input->IsKeyState(KEY::LEFT, KEY_STATE::HOLD))
// 		{
// 			roll(-0.15f);
// 		}
// 		if (input->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD))
// 		{
// 			roll(0.15f);
// 		}
}

void ImpToolModule::ToolCamera::Finalize()
{

}

