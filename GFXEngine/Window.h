#pragma once
#include <Windows.h>

class Window
{
public:
	INT Init(HINSTANCE _hinstance, UINT _width, UINT _height);
	BOOL Update();
	void DeInit();

	HWND GetWindowHandle() { return p_hWnd; }

private:
	HWND p_hWnd = nullptr;
};

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

