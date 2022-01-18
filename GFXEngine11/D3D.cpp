#include "D3D.h"
#include "Utils.h"
#include <xutility>

INT D3D::Init(HWND _hwnd, UINT _width, UINT _height, BOOL _fullscreen)
{	
	HRESULT hr;

	//Set up Presentation Params
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.OutputWindow = _hwnd;
	swapChainDesc.Windowed = !_fullscreen;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Width = _width;
	swapChainDesc.BufferDesc.Height = _height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.SampleDesc.Count = 1; // this MSAA count has to be set to atleast 1


	//Create Device
	D3D_FEATURE_LEVEL supportedFeatureLevels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	D3D_FEATURE_LEVEL choosenFreatureLevel = {};

	
	hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr, //use Primary Graphics Card
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0, //Flags
		supportedFeatureLevels, // Suporrted Versions of Direct X
		std::size(supportedFeatureLevels),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&p_DXGISwapChain,
		&p_D3DDevice,
		&choosenFreatureLevel,
		&p_D3DDeviceContext
	);
	CheckFailed(hr, 20);

	//Create Render Target View
	ID3D11Texture2D* p_BackBufferTexture = nullptr;
	//hr = p_DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&p_BackBufferTexture));
	hr = p_DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&p_BackBufferTexture));
	CheckFailed(hr, 22);

	hr = p_D3DDevice->CreateRenderTargetView(p_BackBufferTexture, nullptr, &p_RenderTargetView);
	CheckFailed(hr, 24);

	SafeRelease<ID3D11Texture2D>(p_BackBufferTexture);

	//Set Viewport
	D3D11_VIEWPORT viewPort = {}; // Describe area projectes onto screen/Window
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = _width;
	viewPort.Height = _height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	//Set Up Render pipeline
	p_D3DDeviceContext->OMSetRenderTargets(1, &p_RenderTargetView, nullptr);
	p_D3DDeviceContext->RSSetViewports(1, &viewPort);

	return 0;
}

void D3D::BeginScene(FLOAT _red, FLOAT _green, FLOAT _blue)
{
	//Clear Back Buffer
	FLOAT backgroundColor[] = { _red, _green, _blue, 1.0f };
	p_D3DDeviceContext->ClearRenderTargetView(p_RenderTargetView, backgroundColor);

	//// Clear back-buffer with solid Color
	//p_D3DDevice->Clear(
	//	0, //Whole Buffer
	//	nullptr, //Rerender all
	//	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // What to Clear ->Taget = Backbuffer
	//	_backgroundcolor,
	//	1.0f,
	//	0xfffffff); // Clears all Values
}

void D3D::EndScene()
{
	//Swap Front and Back Buffer
	p_DXGISwapChain->Present(0, 0);
}

void D3D::DeInit()
{
	SafeRelease<ID3D11Device>(p_D3DDevice);
	SafeRelease<ID3D11DeviceContext>(p_D3DDeviceContext);
	SafeRelease<IDXGISwapChain>(p_DXGISwapChain);
	SafeRelease<ID3D11RenderTargetView>(p_RenderTargetView);
}

