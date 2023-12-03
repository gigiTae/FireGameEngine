#pragma once

#include "FireGameEngine/Engine.h"

class Application
{
public:
	Application();
	~Application();

	void Initialize();
	void Uninitialize();

private:
	Fire::EngineModule::Engine engine;

};

