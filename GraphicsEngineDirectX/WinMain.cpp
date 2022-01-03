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

int WINAPI WinMain(HINSTANCE _hinstance, HINSTANCE _hprevinstance, LPSTR _lpcmdline, int _ncmdshow)
{
	const LPCWSTR p_CLASSNAME = L"EngineWindow";
	UINT width = 1000;
	UINT height = 1000;

	// -->Register Window Class<--
	//Create Window Class
	WNDCLASSEX wc = { 0 };

	//Init Window Class
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hinstance; //App Instance
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = p_CLASSNAME;
	wc.hIconSm = nullptr;

	//Register Window
	if (!RegisterClassEx(&wc)) { return 10; }

	//Window Adjustment
	UINT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	UINT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT wr = { (screenWidth - width) / 2, (screenHeight - height) / 2, (screenWidth + width) / 2, (screenHeight + height) / 2 };
	DWORD style = WS_OVERLAPPEDWINDOW;

	AdjustWindowRect(&wr, style, false);

	// -->Create Window<--
	HWND hWnd = CreateWindow(
		p_CLASSNAME, //ClassName
		L"Your MAMA", //WindowName
		style, //Style
		wr.left, //PosX
		wr.top, //PosY
		wr.right - wr.left, //Width
		wr.bottom - wr.top, //Height
		nullptr, //Parent Window
		nullptr, // Menu Instance
		_hinstance,
		nullptr); // optional Param

	if (hWnd == nullptr) { return 11; }

	// -->Show Window<--
	ShowWindow(hWnd, _ncmdshow);
	SetFocus(hWnd);

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