#pragma once

#define WIN32_LEAN_AND_MEAN

#include "IImpGraphicsEngine.h"

/// <summary>
/// Graphics Engine 을 Game Engine에서 가져다 쓸 때 사용할 h를 따로 뽑아야 겠다. 아닌가 렌더러 정도면 충분히 큰 거 같기도?
/// 어떻게, 뭐가 필요한지는 좀 더 고민을 해봐야겠다.
/// 게임의 Scene 마다 포워드 렌더링이 필요할 지, 디퍼드 렌더링이 필요할 지 다를 수 있겠다. 
/// 그럼 둘다 지원하는 게 맞는 방향이겠지?
/// </summary>
namespace ImpGraphics
{
	/// <summary>
	/// 렌더러 인터페이스
	/// 
	/// 일단은 잘 모르겠어서 교수님의 I3DRenderer.h를 참고했다!
	/// 
	/// 2023.12.12 kimyujin
	/// </summary>
	class IImp3DRenderer abstract
	{
	public:
		IImp3DRenderer() {};
		virtual ~IImp3DRenderer() {};

		/// 가장 기본적으로 렌더러가 돌아가기 위해 필요한 필수 함수
		// 아직 디퍼드는 고려하지 않았다. 
		virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) abstract;
		virtual void Update(float deltaTime) abstract;
		virtual void BeginRender() abstract; // 게임 엔진에서 BeginRender, Render, EndRender 를 구분해서 호출해야 할 이유가 있을까?
		virtual void Render() abstract;
		virtual void EndRender() abstract;
		virtual void Finalize() abstract;

		// 창 변환 관련
		virtual void SetClientSize(int width, int height) abstract;
		// 여기 있어야 하는 이유를 모르겠다.
		//virtual void SetWinMinMax(bool isMinimized, bool isMaxmized) abstract;

		// temp
		virtual void* GetDevice() abstract;
		virtual void* GetDeviceContext() abstract;

		virtual void SetLight(LightInfo lightInfo) abstract;
		virtual void SetCamera(CameraInfo cameraInfo) abstract;
		virtual void SetMeshObject(MeshObjectInfo meshObjectInfo) abstract;
	};
}