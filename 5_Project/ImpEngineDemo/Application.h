#pragma once

namespace ImpGameEngine { class IImpEngine; }

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
	ImpGameEngine::IImpEngine* _gameEngine; 
	ImpGameEngine::WindowInfomation _info;
};

