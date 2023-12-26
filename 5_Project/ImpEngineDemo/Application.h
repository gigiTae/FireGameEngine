#pragma once

class Application
{
public:
	Application();
	~Application();

public:

	/// �ʱ�ȭ �Լ�
	void Initialize(HINSTANCE hInstance);
	
	/// Run Application
	void Process();

	/// ����
	void Finalize();
	
private:
	void InitializeWindow(HINSTANCE hInstance);

private:
	ImpGameEngine::ImpGameEngine _gameEngine; 
	ImpGameEngine::WindowInfomation _info;
};

