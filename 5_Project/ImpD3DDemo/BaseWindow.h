#pragma once
#pragma once
#include <windows.h>

/// <summary>
/// WinAPI�� message�� ���� ����ϰ� �ٷ�� ���� ����� ����
/// 
/// msdn ������ �������� �籸�� �غô�.
/// https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/managing-application-state-
/// �����ڵ�
/// https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/begin/LearnWin32/BaseWindow
/// 
/// KGIT 5�� 1�� ������
/// </summary>
/// <typeparam name="DERIVED_TYPE">��ӹ޴� Ŭ���� ���� �־��ָ� �ȴ�.</typeparam>
template <class DERIVED_TYPE>
class BaseWindow
{
public:
	BaseWindow(PCWSTR className = L"No Name") : m_hWnd(NULL), m_className(className) { }

	/// <summary>
	/// CRTP�� ����ؼ� windowProc�� Ŭ������ ��� �Լ��� ���� �� �ְ� ���ִ� �ٽ�
	/// </summary>
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVED_TYPE* pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			// ���� ������
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;

			// CreateWindowEx �Լ��� ȣ���� �� �־��� this ������(������ �Ķ����)�� ������ (����ڰ� �־��� ��)
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;

			// â�� Ư���� ����
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			// �ؿ��� Create�� �� m_hwnd �־��شٴ� �� pThis->m_hwnd �� �־��ִ� �Ŷ� ���� �� �ƴұ�?
			// �ƴϴ�...!...?
			pThis->m_hWnd = hwnd;
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		// pThis�� ���� �ƴ϶�� == â�� ���� �Ǿ��ٸ�
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	/// <summary>
	/// �׻� ���� hWnd�� ����� �Լ�
	/// 
	/// hWnd ������ �����ϸ� false�� �����Ѵ�.
	/// </summary>
	BOOL CreateHWND(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		DWORD dwExStyle = 0,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	)
	{
		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = m_className;

		RegisterClass(&wc);

		RECT rect;
		SetRect(&rect, 0, 0, nWidth, nHeight);
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		m_hWnd = CreateWindowEx(
			dwExStyle, m_className, lpWindowName, dwStyle, x, y,
			rect.right - rect.left, rect.bottom - rect.top, hWndParent, hMenu, GetModuleHandle(NULL), this
		);

		return (m_hWnd ? TRUE : FALSE);
	}

	HWND GetHWND() const { return m_hWnd; }

protected:
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) abstract;

	HWND m_hWnd;
	PCWSTR m_className; // �̰� �����͸� �����ؾ� �ϳ�?

	//virtual PCWSTR  ClassName() const abstract; �Լ��� ����� ������ �𸣰ڴ�. �Լ� �� �� �� ȣ���� �Ÿ� �׳� ������ ���� �ʳ�? 
};