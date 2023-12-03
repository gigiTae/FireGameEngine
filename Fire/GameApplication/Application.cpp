#include "Application.h"



Application::Application()
{
}

Application::~Application()
{
}

void Application::Initialize()
{
	engine.Initialize();
	engine.Process();
}

void Application::Uninitialize()
{
	engine.Uninitialize();
}
