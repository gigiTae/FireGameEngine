#pragma once

namespace ImpEngineModule
{
	/// <summary>
	/// �Է¿� ���� ó���� �ϴ� Ŭ����
	/// ex) ���콺, Ű���� ���
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

		// �̹� ������ ���콺 ��ġ
		POINT GetMousePosition()const { return currentMousePosition; }
		// �̹� ������ ���콺 ��ȭ��
		POINT GetDeltaMousePosition()const { return deltaMousePosition; }

	private:
		HWND _hwnd; // ���� ������ �ڵ�
		std::vector<KeyInfo> _keyInfo;	// Ű �������� ���� �迭
		const int _matchVK[static_cast<int>(KEY::LAST)];// KEY ���� ����Ű���� ��Ī�����ִ� �迭

		POINT currentMousePosition; // ���� ������ ���콺 ��ġ
		POINT prevMousePosition; // ���� ������ ���콺 ��ġ
		POINT deltaMousePosition; // �̹������� ���콺 ��ȭ�� 
	};
}
