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
	
	// 람다캡처
	RendererModule::Camera* renderCamera = cameraModule;

	InputManager* input  = InputManager::GetInstance();

	world->Each<Camera, Transform>([input, renderCamera,dt](Entity* ent,
		ComponentHandle<Camera> camera, ComponentHandle<Transform> transform)
		{
			Vector3 pos = transform->position;
			Vector3 rotation = transform->rotation;

			float distance = camera->cameraSpeed * dt;

			// 메인 카메라를 움직인다.
			if (!camera->isMain)
				return;

			/// 카메라 키입력 처리 LMOUSE 버튼을 누르고 있으면 움직인다.
			if (input->IsKeyState(KEY::LMOUSE, KEY_STATE::HOLD))
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

				/// 시선 회전
				POINT dt = input->GetDeltaMousePosition();
				
				renderCamera->Pitch(dt.y);
				renderCamera->RotateY(dt.x);
				
				XMFLOAT3 pos = renderCamera->GetPosition();
				transform->position = { pos.x,pos.y,pos.z };

				XMFLOAT3 rot = renderCamera->GetRotationFromViewMatrix();
				transform->rotation = { rot.x,rot.y,rot.z };
			}



		}, false);
}
