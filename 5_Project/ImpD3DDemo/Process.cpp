#include "pch.h"
#include "Process.h"

#include "../ImpGraphicsEngine/IImpGraphicsEngine.h"
using namespace ImpGraphics;

Process::Process()
	: m_timer(nullptr),
	m_windowPosX(300), m_windowPosY(300),
	m_screenWidth(900), m_screenHeight(600),
	m_resizing(false),
	m_pRenderer(nullptr)
{
	CreateHWND(L"D3DEngine Demo", WS_OVERLAPPEDWINDOW, m_windowPosX, m_windowPosY, m_screenWidth, m_screenHeight);
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	m_pRenderer = EngineExporter::GetEngine();
}

Process::~Process()
{
	EngineExporter::DeleteEngine();
}

bool Process::Init(HINSTANCE hInstance)
{
#pragma warning(disable : 4311)
#pragma warning(disable : 4302)
	m_pRenderer->Initialize((int)hInstance, (int)m_hWnd, m_screenWidth, m_screenHeight);
#pragma warning(default : 4311)
#pragma warning(default : 4302)

	InputManager::GetInstance().Init(m_hWnd);
	m_timer = std::make_unique<GameTimer>();
	m_timer->Reset();

// 	MeshObjectInfo info;
// 	info._objectID = 1;
// 	info._meshPath = L"Resources/Imp/mm.fbx";
// 	info._pisxelShaderPath = L"../ImpGraphicsEngine/FirstNormalPS.hlsl";
// 	info._vertexShaderPath = L"../ImpGraphicsEngine/FirstNormalVS.hlsl";
// 
// 	m_pRenderer->AddMeshObejct(info);

// 	info;
// 	info._objectID = 2;
// 	info._meshPath = L"Resources/Imp/dd.fbx";
// 	info._pisxelShaderPath = L"../ImpGraphicsEngine/FirstNormalPS.hlsl";
// 	info._vertexShaderPath = L"../ImpGraphicsEngine/FirstNormalVS.hlsl";
// 
// 	m_pRenderer->AddMeshObejct(info);

// 	info;
// 	info._objectID = 3;
// 	info._meshPath = L"Resources/Imp/Axis.fbx";
// 	info._pisxelShaderPath = L"../ImpGraphicsEngine/FirstNormalPS.hlsl";
// 	info._vertexShaderPath = L"../ImpGraphicsEngine/FirstNormalVS.hlsl";
// 
// 	m_pRenderer->AddMeshObejct(info);

// 	Matrix iden = Matrix::Identity();
// 	m_pRenderer->SetMeshObject(1, iden);
// 	m_pRenderer->SetMeshObject(2, iden);
	//m_pRenderer->SetMeshObject(3, iden);

	return true;
}

void Process::Loop()
{
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
 			Update();
 			Render();
		}
	}
}

void Process::Finalize()
{

}

// IMGUI를 쓰려면 필요하다.
//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT Process::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	//if (ImGui_ImplWin32_WndProcHandler(m_hWnd, uMsg, wParam, lParam))
		//return true;

	switch (uMsg)
	{
		case WM_SIZE:
		{
			if (m_pRenderer == nullptr)
			{
				return 0;
			}
			m_pRenderer->SetClientSize(LOWORD(lParam), HIWORD(lParam));
		}
		// WM_SIZE is sent when the user resizes the window.  
// 		case WM_SIZE:
// 		{
// 			if (m_pRenderer == nullptr)
// 			{
// 				return 0;
// 			}
// 			// Save the new client area dimensions.
// 			m_pRenderer->SetClientSize(LOWORD(lParam), HIWORD(lParam));
// 
// 			if (m_pRenderer->IsValidDevice())
// 			{
// 				if (wParam == SIZE_MINIMIZED)
// 				{
// 					//mAppPaused = true;
// 					m_pRenderer->SetWinMinMax(true, false);
// 				}
// 				else if (wParam == SIZE_MAXIMIZED)
// 				{
// 					//mAppPaused = false;
// 					m_pRenderer->SetWinMinMax(false, true);
// 					m_pRenderer->OnResize();
// 				}
// 				else if (wParam == SIZE_RESTORED)
// 				{
// 					// Restoring from minimized state?
// 					// Restoring from maximized state?
// 					if (mResizing)
// 					{
// 						// If user is dragging the resize bars, we do not resize 
// 						// the buffers here because as the user continuously 
// 						// drags the resize bars, a stream of WM_SIZE messages are
// 						// sent to the window, and it would be pointless (and slow)
// 						// to resize for each WM_SIZE message received from dragging
// 						// the resize bars.  So instead, we reset after the user is 
// 						// done resizing the window and releases the resize bars, which 
// 						// sends a WM_EXITSIZEMOVE message.
// 					}
// 					else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
// 					{
// 						m_pRenderer->SetWinMinMax(false, false);
// 
// 						m_pRenderer->OnResize();
// 					}
// 				}
// 			}
// 		}
// 		return 0;
// 
// 		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
// 		case WM_ENTERSIZEMOVE:
// 		{
// 			//mAppPaused = true;
// 			mResizing = true;
// 			//mTimer.Stop();
// 		}
// 		return 0;
// 
// 		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
// 		// Here we reset everything based on the new window dimensions.
// 		case WM_EXITSIZEMOVE:
// 		{
// 			//mAppPaused = false;
// 			mResizing = false;
// 			//mTimer.Start();
// 			m_pRenderer->OnResize();
// 		}
// 		return 0;

		case WM_PAINT:
			hdc = BeginPaint(m_hWnd, &ps);
			EndPaint(m_hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void Process::UpdateTimer()
{
	// 매 프레임 시간을 계산한다.
	m_timer->Tick();

	// 매 프레임의 deltaTime
	m_timer->DeltaTime();

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	/// 타이머를 기반으로 FPS, millisecond per frame (1프레임당 elapsedTime = deltaTime)을 계산 해 준다.

	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((m_timer->TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void Process::Update()
{
	InputManager::GetInstance().Update();
	UpdateTimer();
	/// 카메라 사용 예시
	ImpGraphics::CameraInfo cameraInfo;

	cameraInfo._position = pos;
	cameraInfo._rotation = rot;
	cameraInfo._scale = scale;
	cameraInfo._isPerspective = isPerspective;
	cameraInfo._fieldOfView = fov;
	cameraInfo._nearPlain = nearP;
	cameraInfo._farPlain = farP;

	m_pRenderer->SetCamera(cameraInfo);
	///

	if (InputManager::GetInstance().IsGetKey('W'))
	{
		Walk(0.001f);
	}
	if (InputManager::GetInstance().IsGetKey('S'))
	{
		Walk(-0.001f);
	}
	if (InputManager::GetInstance().IsGetKey('D'))
	{
		Strafe(0.001f);
	}
	if (InputManager::GetInstance().IsGetKey('A'))
	{
		Strafe(-0.001f);
	}
	if (InputManager::GetInstance().IsGetKey('E'))
	{
		WorldUpDown(0.001f);
	}
	if (InputManager::GetInstance().IsGetKey('Q'))
	{
		WorldUpDown(-0.001f);
	}
	static Matrix aa = Matrix::Identity();
	if (InputManager::GetInstance().IsGetKey('V'))
	{
		aa._21 += 0.001f;
		m_pRenderer->SetMeshObject(1, aa);
	}
	if (InputManager::GetInstance().IsGetKeyDown('B'))
	{

	}

	if (InputManager::GetInstance().IsGetKey(VK_RBUTTON))
	{
		float dx = (2.25f * static_cast<float>(InputManager::GetInstance().GetDeltaPosition().x) * (3.141592f / 180.0f));
		float dy = (2.25f * static_cast<float>(InputManager::GetInstance().GetDeltaPosition().y) * (3.141592f / 180.0f));
		
		//RotateY(dx);
		Pitch(dy);
		Yaw(dx);
	}

	/// 엔진 업데이트
	m_pRenderer->Update(m_timer->DeltaTime());
}

void Process::Render()
{
	/// 그리기를 준비한다.
 	m_pRenderer->BeginRender();
 
 	/// 엔진만의 그리기를 한다.
 	m_pRenderer->Render(IImpGraphicsEngine::RendererType::Forward);
 
 	/// 그리기를 끝낸다.
 	m_pRenderer->EndRender();
}

void Process::Strafe(float distance)
{
	//mPosition = XMFLOAT3(mRight.x * d + mPosition.x, mRight.y * d + mPosition.y, mRight.z * d + mPosition.z);
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rot);

	pos = ImpMath::Vector3(_rotMatrix._11 * distance + pos.x,
		_rotMatrix._12 * distance + pos.y, _rotMatrix._13 * distance + pos.z);
}

void Process::Walk(float distance)
{
	//mPosition = XMFLOAT3(mLook.x * d + mPosition.x, mLook.y * d + mPosition.y, mLook.z * d + mPosition.z);
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rot);

	pos = ImpMath::Vector3(_rotMatrix._31 * distance + pos.x,
		_rotMatrix._32 * distance + pos.y, _rotMatrix._33 * distance + pos.z);
}

void Process::WorldUpDown(float distance)
{
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rot);

	pos = ImpMath::Vector3(_rotMatrix._21 * distance + pos.x,
		_rotMatrix._22 * distance + pos.y, _rotMatrix._23 * distance + pos.z);
}

void Process::Yaw(float angle)
{
	ImpMath::Vector3 rotation = rot;
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rotation);

	ImpMath::Vector3 up{ 0, 1, 0 };
	up = up.Normalize();

	rotation += up * angle;
	rot = rotation;
}

void Process::Pitch(float angle)
{
	ImpMath::Vector3 rotation = rot;
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rotation);

	ImpMath::Vector3 right{ 1, 0, 0 };
	right = right.Normalize();

	rotation += right * angle;
	rot = rotation;
}

void Process::Roll(float angle)
{
	ImpMath::Vector3 rotation = rot;
	_rotMatrix = ImpMath::Matrix::MakeRotationMatrixRollPitchYaw(rotation);

	ImpMath::Vector3 look{ 0, 0, 1 };
	look = look.Normalize();

	rotation += look * angle;
	rot = rotation;
}