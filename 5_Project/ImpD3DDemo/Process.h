#pragma once
#include "pch.h"

#include "BaseWindow.h"
#include "GameTimer.h" // �ϴ��� Demo �̹Ƿ� ������ Time ������ �ʿ� ���ٰ� �����ϰ� �׳� ������ ����.

#include "../ImpStructure/ImpMath.h"

// Todo: ��� ��� ���� ���ϰ� �����ؾ� ��
namespace ImpGraphics { class IImpGraphicsEngine; }

class Process : public BaseWindow<Process>
{
public:
	///  ---------- ������, �Ҹ��� ----------
	Process();
	~Process();

	/// ---------- �⺻ ���� ----------
	bool Init(HINSTANCE hInstance);
	void Loop();
	void Finalize();

	/// ---------- ������ �޼��� ó�� ----------
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
	// �ð� ����
	std::unique_ptr<GameTimer> m_timer;

private:
	/// ---------- ó�� ������ �� �ʿ��� ��� �� ----------
	// ������ �ʱ� ��ġ
	const int m_windowPosX;
	const int m_windowPosY;

	// ȭ�� ũ��
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