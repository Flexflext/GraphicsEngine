#pragma once
#include <Windows.h>
#include "D3D.h"

class Window
{
public:
	INT Init(HINSTANCE _hinstance, UINT _width, UINT _height);
	BOOL Update();
	void DeInit();

	//void SetResizeFunc(D3D* _p_direct11) { p_direct11 = _p_direct11; }
	HWND GetWindowHandle() { return p_hWnd; }
	D3D d3d = {};

private:
	HWND p_hWnd = nullptr;
	MSG msg = {};
	
};

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

