#pragma once

namespace ImpEngineModule
{
	/// <summary>
	/// 입력에 관한 처리를 하는 클래스
	/// ex) 마우스, 키보드 등등
	/// </summary>
	class InputManager
	{
		struct KeyInfo
		{
			KEY_STATE state;
			bool prevPush;
		};

	public:
		static InputManager* GetInstance() { static InputManager input; return &input; }

	public:
		InputManager();
		~InputManager();

		void Initalize(HWND main);
		void Update();
		void Finalize();

		KEY_STATE GetKeyState(KEY _key)const { return _keyInfo[static_cast<int>(_key)].state; }
		bool IsKeyState(const KEY& _key, const KEY_STATE& _state) const;

		// 이번 프레임 마우스 위치
		POINT GetMousePosition()const { return currentMousePosition; }
		// 이번 프레임 마우스 변화량
		POINT GetDeltaMousePosition()const { return deltaMousePosition; }

	private:
		HWND _hwnd; // 메인 윈도우 핸들
		std::vector<KeyInfo> _keyInfo;	// 키 정보들을 담은 배열
		const int _matchVK[static_cast<int>(KEY::LAST)];// KEY 값을 가상키값과 매칭시켜주는 배열

		POINT currentMousePosition; // 현재 프레임 마우스 위치
		POINT prevMousePosition; // 이전 프레임 마우스 위치
		POINT deltaMousePosition; // 이번프레임 마우스 변화량 
	};
}
