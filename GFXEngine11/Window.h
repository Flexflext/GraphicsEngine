//Script to Initialize a Win32 Window
#pragma once
#include <Windows.h>
#include "D3D.h"

class Window
{
public:
	//-> Singelton Logic
	Window(Window& other) = delete;
	void operator=(const Window&) = delete;

	/// <summary>
	/// Get Instance of Window
	/// </summary>
	/// <returns>Singelton Instance</returns>
	static Window* GetInstance();

	/// <summary>
	/// Initialzes the Window
	/// </summary>
	/// <param name="_hinstance">HINSTANCE of the App</param>
	/// <param name="_width">Window Width</param>
	/// <param name="_height">Window Height</param>
	/// <returns></returns>
	INT Init(HINSTANCE _hinstance, UINT _width, UINT _height);
	/// <summary>
	/// Updates Window
	/// </summary>
	/// <returns>Bool to Stop the Window</returns>
	BOOL Update();
	/// <summary>
	/// DeInitializes the Window
	/// </summary>
	void DeInit();

	/// <summary>
	/// Get the Window Handle
	/// </summary>
	/// <returns>Window Handle</returns>
	HWND GetWindowHandle() { return p_hWnd; }

private:
	//Window Handle
	HWND p_hWnd = nullptr;
	//Message to get from Win32
	MSG msg = {};
	
	//Instance of the Window Class
	static Window* Instance;

	//Singelton Logic (no public construction)
	Window()
	{

	}
};

/// <summary>
/// Window Proc Custom Message Handler
/// </summary>
/// <param name="_hwnd"></param>
/// <param name="_msg"></param>
/// <param name="_wparam"></param>
/// <param name="_lparam"></param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

