﻿// GameApplication.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "Application.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Application app;

	app.Initialize();

	app.Uninitialize();


	return 0;
}