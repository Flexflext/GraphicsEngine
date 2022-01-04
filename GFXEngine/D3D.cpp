#include "D3D.h"
#include "Utils.h"

INT D3D::Init(HWND _hwnd, UINT _width, UINT _height, BOOL _fullscreen)
{
	//Get Direct3D Interface
	IDirect3D9* p_D3D = Direct3DCreate9(D3D_SDK_VERSION);
	CheckNull(p_D3D, 20);

	//Check fixed-function pipeline support
	D3DCAPS9 d3dCaps = {};
	UINT adapter = D3DADAPTER_DEFAULT; // Graphics Card = = Primary
	D3DDEVTYPE deviceType = D3DDEVTYPE_HAL; // renderer HAL Hardware Abstraction Layer (Graphics Card)
	HRESULT hr = p_D3D->GetDeviceCaps(adapter, deviceType, &d3dCaps);
	CheckFailed(hr, 22);

	DWORD vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //fallback
	if (d3dCaps.VertexProcessingCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	//Set up Presentation Params
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.hDeviceWindow = _hwnd; // Render-Target
	d3dpp.Windowed = !_fullscreen; // Windowed or Exclusive fullscreen
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = _width;
	d3dpp.BackBufferHeight = _height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // what should happen with the frontbuffer


	//Create Device
	hr = p_D3D->CreateDevice(
		adapter,
		deviceType,
		_hwnd,
		vertexProcessing, //Optional Parameters
		&d3dpp,
		&p_D3DDevice);

	CheckFailed(hr, 24);

	//Tidy up
	SafeRelease<IDirect3D9>(p_D3D);

	return 0;
}

void D3D::BeginScene(D3DCOLOR _backgroundcolor)
{
	// Clear back-buffer with solid Color
	p_D3DDevice->Clear(
		0, //Whole Buffer
		nullptr, //Rerender all
		D3DCLEAR_TARGET, // What to Clear ->Taget = Backbuffer
		_backgroundcolor,
		1.0f,
		0xfffffff); // Clears all Values

	p_D3DDevice->BeginScene();
}

void D3D::EndScene()
{
	p_D3DDevice->EndScene();

	//Swap Front and Back Buffer
	p_D3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void D3D::DeInit()
{
	SafeRelease<IDirect3DDevice9>(p_D3DDevice);
}

