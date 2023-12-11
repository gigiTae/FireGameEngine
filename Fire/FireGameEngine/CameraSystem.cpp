#include "FireGameEnginepch.h"
#include "CameraSystem.h"
#include "InputManager.h"
#include "InputEnumClass.h"

Fire::ECS::CameraSystem::CameraSystem(RendererModule::Camera* camera)
	:cameraModule(camera)
{

}

Fire::ECS::CameraSystem::~CameraSystem()
{

}

void Fire::ECS::CameraSystem::Tick(World* world, float dt)
{
	using namespace Fire::Component;

	// ����ĸó
	RendererModule::Camera* renderCamera = cameraModule;

	InputManager* input = InputManager::GetInstance();

	world->Each<Camera, Transform>([input, renderCamera, dt](Entity* ent,
		ComponentHandle<Camera> camera, ComponentHandle<Transform> transform)
		{
			Vector3 pos = transform->position;
			Vector3 rotation = transform->rotation;

			float distance = camera->cameraSpeed * dt;

			// ���� ī�޶� �����δ�.
			if (!camera->isMain)
				return;

			/// ī�޶� Ű�Է� ó�� RMOUSE ��ư�� ������ ������ �����δ�.
			if (input->IsKeyState(KEY::RMOUSE, KEY_STATE::HOLD))
			{
				if (input->IsKeyState(KEY::W, KEY_STATE::HOLD))
				{
					// Foward
					renderCamera->Walk(distance);
				}
				if (input->IsKeyState(KEY::S, KEY_STATE::HOLD))
				{
					// Back
					renderCamera->Walk(-distance);
				}
				if (input->IsKeyState(KEY::A, KEY_STATE::HOLD))
				{
					// Left
					renderCamera->Strafe(-distance);
				}
				if (input->IsKeyState(KEY::D, KEY_STATE::HOLD))
				{
					// Right
					renderCamera->Strafe(distance);
				}

				/// �ü� ȸ��
				POINT dt = input->GetDeltaMousePosition();

				float senssitivity = camera->sensitivity;

				float dX = static_cast<float>(dt.x) / senssitivity;
				float dY = static_cast<float>(dt.y) / senssitivity;

				renderCamera->Pitch(dY);
				renderCamera->RotateY(dX);

				XMFLOAT3 pos = renderCamera->GetPosition();
				transform->position = { pos.x,pos.y,pos.z };

				XMFLOAT3 rot = renderCamera->GetRotationFromViewMatrix();
				transform->rotation = { rot.x,rot.y,rot.z };
			}
		}, false);
}
