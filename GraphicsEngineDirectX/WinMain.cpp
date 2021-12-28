#include <Windows.h>

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
		case WM_CLOSE:
			PostQuitMessage(69);
			break;
	}

	return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
}

int CALLBACK WinMain(HINSTANCE _hinstance, HINSTANCE _hprevinstance, LPSTR _lpcmdline, int _ncmdshow)
{
	const LPCWSTR p_CLASSNAME = L"EngineWindow";

	// -->Register Window Class<--
	//Create Window Class
	WNDCLASSEX wc = { 0 };

	//Init Window Class
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hinstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = p_CLASSNAME;
	wc.hIconSm = nullptr;

	//Register Window
	RegisterClassEx(&wc);

	// -->Create Window<--
	HWND hWnd = CreateWindowEx(
		0,
		p_CLASSNAME, //ClassName
		L"Your MAMA", //WindowName
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Style
		1000, //PosX
		200, //PosY
		1000, //Width
		200, //Height
		nullptr,
		nullptr,
		_hinstance,
		nullptr);

	// -->Show Window<--
	ShowWindow(hWnd, SW_SHOW);

	// -->Message Pump<--
	MSG message;
	BOOL gResult;

	while ((gResult = GetMessage(&message, nullptr, 0,0)))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return message.wParam;
	}	
}