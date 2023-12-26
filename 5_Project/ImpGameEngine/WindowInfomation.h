#pragma once

#include "ExportDefine.h"

namespace ImpGameEngine
{
	struct IMP_ENGNIE_API WindowInfomation
	{
		static LONG resizeWidth;
		static LONG resizeHegiht;

		HINSTANCE _hInstance = NULL;
		HWND _hWnd = NULL;
		LONG _screenLeft = 0;
		LONG _screenTop = 50;
		LONG _screenWidth = 1280;
		LONG _screenHeight = 960;
	
		const wchar_t* _title = L"Imp";

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};

}