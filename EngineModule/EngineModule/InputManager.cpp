#include "EngineModulePCH.h"
#include "InputManager.h"


ImpEngineModule::InputManager::InputManager()
	:_matchVK{
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		'Q','W','E','R','T','Y','U','O','P',
		'A','S','D','F','G','H','J','K','L',
		'Z','X','C','V','B','N','M',

		VK_MENU, // ALT,
		VK_CONTROL, // CTRL,
		VK_LSHIFT, // LSHIFT,
		VK_SPACE, // SPACE,
		VK_RETURN, // ENTER,
		VK_ESCAPE, // ESC,
		VK_TAB, //TAB

		VK_LBUTTON, // LBTN
		VK_RBUTTON, // RBTN

		VK_F1, // F1
		VK_F2, // F2
		VK_F3, // F3
		VK_F4, // F4
		VK_F5, // F5
	}
	, _keyInfo{}
	, _hwnd(nullptr)
	, currentMousePosition{}
	, prevMousePosition{}
	, deltaMousePosition{}
{

}

ImpEngineModule::InputManager::~InputManager()
{

}

void ImpEngineModule::InputManager::Initalize(HWND main)
{
	_hwnd = main;

	for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
	{
		_keyInfo.push_back(KeyInfo{ KEY_STATE::NONE,false });
	}
}

void ImpEngineModule::InputManager::Update()
{

	HWND hWnd = GetFocus();

	// 현재 포커스중일때
	if (nullptr != hWnd)
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			if (GetAsyncKeyState(_matchVK[i]) & 0x8000)
			{
				if (_keyInfo[i].prevPush)
				{
					_keyInfo[i].state = KEY_STATE::HOLD;
				}
				else
				{
					_keyInfo[i].state = KEY_STATE::TAP;
				}
				_keyInfo[i].prevPush = true;
			}
			else
			{
				if (_keyInfo[i].prevPush)
				{
					_keyInfo[i].state = KEY_STATE::AWAY;
				}
				else
				{
					_keyInfo[i].state = KEY_STATE::NONE;
				}
				_keyInfo[i].prevPush = false;
			}
		}


		prevMousePosition = currentMousePosition;

		// Mouse 위치 계산
		GetCursorPos(&currentMousePosition);

		// 스크린 좌표계의 마우스 위치
		ScreenToClient(_hwnd, &currentMousePosition);

		// 마우스가 이번프레임에 얼마나 움직였는지
		deltaMousePosition = { currentMousePosition.x - prevMousePosition.x,
		 currentMousePosition.y - prevMousePosition.y };



	}
	// 포커스해제되어 예외처리 진행
	else
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			_keyInfo[i].prevPush = false;
			if (KEY_STATE::TAP == _keyInfo[i].state || KEY_STATE::HOLD == _keyInfo[i].state)
			{
				_keyInfo[i].state = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == _keyInfo[i].state)
			{
				_keyInfo[i].state = KEY_STATE::NONE;
			}

		}
	}
}

void ImpEngineModule::InputManager::Finalize()
{
	_keyInfo.clear();
}

bool ImpEngineModule::InputManager::IsKeyState(const KEY& _key, const KEY_STATE& _state) const
{
	if (_state == GetKeyState(_key))
	{
		return true;
	}

	return false;
}
