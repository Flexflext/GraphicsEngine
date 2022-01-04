#include "Window.h"
#include "Utils.h"

INT Window::Init(HINSTANCE _hinstance, UINT _width, UINT _height)
{
	// -->Register Window Class<--
	//Create Window Class
	WNDCLASS wc = {};
	// -> Creates a window class object
	wc.hInstance = _hinstance;
	// -> handle to application instance
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	// -> handle to background brush (colour)
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// -> handle to application cursor
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	// -> handle to application icon
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	// -> additional window behaviour
	wc.lpszClassName = TEXT("First Window");
	// -> window class name
	wc.lpfnWndProc = WndProc;

	//Register Window
	if (!RegisterClass(&wc)) { return 10; }

	//Window Adjustment
	UINT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	UINT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT wr = { (screenWidth - _width) / 2, (screenHeight - _height) / 2, (screenWidth + _width) / 2, (screenHeight + _height) / 2 };
	DWORD style = WS_OVERLAPPEDWINDOW;

	AdjustWindowRect(&wr, style, false);

	// -->Create Window<--
	p_hWnd = CreateWindow(
		wc.lpszClassName, //ClassName
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

	CheckNull(p_hWnd, 11);

	// -->Show Window<--
	ShowWindow(p_hWnd, SW_SHOW);
	SetFocus(p_hWnd);

	return 0;
}

BOOL Window::Update()
{
	// -->Message Pump<--

	static MSG msg = {};

	if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam != WM_QUIT;
}

void Window::DeInit()
{
}

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			if (_wparam == VK_ESCAPE) DestroyWindow(_hwnd);
			break;

		default:
			return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
	}

	return 0;
}
