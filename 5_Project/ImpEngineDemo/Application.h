#pragma once

class Application
{
public:
	Application();
	~Application();

public:

	/// 초기화 함수
	void Initialize(HINSTANCE hInstance);
	
	/// Run Application
	void Process();

	/// 종료
	void Finalize();
	
private:
	void InitializeWindow(HINSTANCE hInstance);

private:
	ImpGameEngine::ImpGameEngine _gameEngine; 
	ImpGameEngine::WindowInfomation _info;
};

