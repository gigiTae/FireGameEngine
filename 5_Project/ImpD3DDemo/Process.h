#pragma once
#include "pch.h"

#include "BaseWindow.h"
#include "GameTimer.h" // 일단은 Demo 이므로 정밀한 Time 관리가 필요 없다고 가정하고 그냥 가져다 쓴다.

#include "../ImpStructure/ImpMath.h"

// Todo: 경로 어떻게 할지 정하고 변경해야 됨
namespace ImpGraphics { class IImpGraphicsEngine; }

class Process : public BaseWindow<Process>
{
public:
	///  ---------- 생성자, 소멸자 ----------
	Process();
	~Process();

	/// ---------- 기본 구조 ----------
	bool Init(HINSTANCE hInstance);
	void Loop();
	void Finalize();

	/// ---------- 윈도우 메세지 처리 ----------
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
	/// ---------- Update & Render ----------
	void UpdateTimer();
	void Update();
	void Render();

private:
	/// ---------- WinAPI, Graphics Engine ----------
	// 3D Graphics Engine
	std::unique_ptr <ImpGraphics::IImpGraphicsEngine> m_pRenderer;
	//ImpGraphics::IImp3DRenderer* m_pRenderer;

	/// ---------- Timer ----------
	// 시간 제어
	std::unique_ptr<GameTimer> m_timer;

private:
	/// ---------- 처음 실행할 때 필요한 상수 값 ----------
	// 윈도우 초기 위치
	const int m_windowPosX;
	const int m_windowPosY;

	// 화면 크기
	const int m_screenWidth;
	const int m_screenHeight;

	bool m_resizing;

	// temp
	ImpMath::Vector3 pos = ImpMath::Vector3(0, 3, -5);
	ImpMath::Vector3 rot = ImpMath::Vector3(30, 0, 0);
	ImpMath::Vector3 scale = ImpMath::Vector3(1, 1, 1);

	bool isPerspective = bool(true);
	float fov = float(0.25f * 3.1415f);
	float nearP = float(0.3f);
	float farP = float(1000.f);
};