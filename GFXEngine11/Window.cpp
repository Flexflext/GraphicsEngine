#include "Window.h"
#include "Utils.h"
#include "D3D.h"
#include "AllCameras.h"
#include "Camera.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_win32.cpp"

//Initialize Static Window Instance
Window* Window::Instance = nullptr;

Window* Window::GetInstance()
{
	if (Instance == nullptr) Instance = new Window();

	return Instance;
}

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
	DWORD style = WS_OVERLAPPEDWINDOW;//WS_SYSMENU;

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
	//Initialize Window UI
	ImGui_ImplWin32_Init(p_hWnd);
	//Set Focus to Window
	SetFocus(p_hWnd);

	return 0;
}

BOOL Window::Update()
{
	// -->Message Pump<--
	if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
	{
		//Give Messages to ImGui
		if (ImGui_ImplWin32_WndProcHandler(p_hWnd, msg.message, msg.wParam, msg.lParam))
		{
			return true;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);		
	}

	//Check if Client wants to Quit
	return msg.message != WM_QUIT;
}

void Window::DeInit()
{
	//DeInit Window
	ImGui_ImplWin32_Shutdown();
}

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
		//Check if to Close the Window
		case WM_CLOSE:
			PostQuitMessage(69);
			return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
			break;
		//Check if to Resize the Window
		case WM_EXITSIZEMOVE:
		{
			//Get new Window Width and Height
			UINT screenWidth = GetSystemMetrics(SM_CXSCREEN);
			UINT screenHeight = GetSystemMetrics(SM_CYSCREEN);
			RECT rect = {};
			GetWindowRect(Window::GetInstance()->GetWindowHandle(), &rect);

			WindowWidth = ((screenWidth + (rect.right - rect.left)) / 2) - ((screenWidth - (rect.right - rect.left)) / 2);
			WindowHeight = ((screenHeight + (rect.bottom - rect.top)) / 2) - ((screenHeight - (rect.bottom - rect.top)) / 2);

			//Resize the DirectX Handle 
			D3D::GetInstance()->OnResize();


			return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
			break;
		}
		default:
			return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
	}

	return 0;
}


