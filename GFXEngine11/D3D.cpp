#include "D3D.h"
#include "Utils.h"
#include <xutility>
#include "Window.h"
#include "imgui/imgui_impl_dx11.h"

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

	//Death Stencil View
	ID3D11Texture2D* p_depthStencilTexture = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilTextureDesc = {};
	depthStencilTextureDesc.Width = _width;
	depthStencilTextureDesc.Height = _height;
	depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilTextureDesc.ArraySize = 1; // at least one texture
	depthStencilTextureDesc.SampleDesc.Count = 1; // should be always 1

	hr = p_D3DDevice->CreateTexture2D(&depthStencilTextureDesc, nullptr, &p_depthStencilTexture);
	CheckFailed(hr, 26);

	hr = p_D3DDevice->CreateDepthStencilView(p_depthStencilTexture, nullptr, &p_depthStencilView);
	CheckFailed(hr, 28);

	SafeRelease<ID3D11Texture2D>(p_depthStencilTexture);

	//Rasterizer State
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;

	hr = p_D3DDevice->CreateRasterizerState(&rasterizerDesc, &p_rasterizerState);
	CheckFailed(hr, 29);

	//Set Viewport
	D3D11_VIEWPORT viewPort = {}; // Describe area projectes onto screen/Window
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = _width;
	viewPort.Height = _height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	//Set Up Render pipeline
	p_D3DDeviceContext->OMSetRenderTargets(1, &p_RenderTargetView, p_depthStencilView);
	p_D3DDeviceContext->RSSetViewports(1, &viewPort);
	p_D3DDeviceContext->RSSetState(p_rasterizerState);


	ImGui_ImplDX11_Init(p_D3DDevice, p_D3DDeviceContext);
	return 0;
}

void D3D::BeginScene(FLOAT _red, FLOAT _green, FLOAT _blue)
{
	if (Resize)
	{
		return;
	}

	//Clear Back Buffer
	FLOAT backgroundColor[] = { _red, _green, _blue, 1.0f };
	p_D3DDeviceContext->ClearRenderTargetView(p_RenderTargetView, backgroundColor);

	//Clear depth buffer
	p_D3DDeviceContext->ClearDepthStencilView(p_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0xffffffff);
}

void D3D::EndScene()
{
	if (Resize)
	{
		return;
	}

	//Swap Front and Back Buffer
	p_DXGISwapChain->Present(0, 0);
}

void D3D::DeInit()
{
	ImGui_ImplDX11_Shutdown();
	SafeRelease<ID3D11DepthStencilView>(p_depthStencilView);
	SafeRelease<ID3D11Device>(p_D3DDevice);
	SafeRelease<ID3D11DeviceContext>(p_D3DDeviceContext);
	SafeRelease<IDXGISwapChain>(p_DXGISwapChain);
	SafeRelease<ID3D11RenderTargetView>(p_RenderTargetView);
	SafeRelease<ID3D11RasterizerState>(p_rasterizerState);
}

void D3D::OnResize()
{
	if (p_DXGISwapChain)
	{
		p_D3DDeviceContext->OMSetRenderTargets(0, 0, 0);

		//// Release all outstanding references to the swap chain's buffers.
		p_RenderTargetView->Release();
		p_D3DDeviceContext->ClearState();

		HRESULT hr;
		// Preserve the existing buffer count and format.
		// Automatically choose the width and height to match the client rect for HWNDs.
		hr = p_DXGISwapChain->ResizeBuffers(1, WindowWidth, WindowHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		//CheckFailed(hr, 25);
		// Perform error handling here!

		DXGI_MODE_DESC desc = {};
		desc.Width = WindowWidth;
		desc.Height = WindowHeight;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		//desc.ArraySize = 1; // at least one texture
		//desc.SampleDesc.Count = 1; // should be always 1

		//p_DXGISwapChain->ResizeTarget(&desc);

		ID3D11Texture2D* p_backBufferTexture = nullptr;
		//// Get buffer and create a render-target-view.
		hr = p_DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&p_backBufferTexture));
		////CheckFailed(hr, 27);
		//// Perform error handling here!

		if (p_RenderTargetView != nullptr)
		{
			if (p_backBufferTexture)
			{
				hr = p_D3DDevice->CreateRenderTargetView(p_backBufferTexture, nullptr, &p_RenderTargetView);
			}	
			//CheckFailed(hr, 29);
		}
		

		SafeRelease<ID3D11Texture2D>(p_backBufferTexture);

		//Resize depth...
		p_D3DDeviceContext->OMSetRenderTargets(1, &p_RenderTargetView, nullptr);

		// Set up the viewport.
		D3D11_VIEWPORT viewPort = {}; // Describe area projectes onto screen/Window
		viewPort.TopLeftX = 0.0f;
		viewPort.TopLeftY = 0.0f;
		viewPort.Width = WindowWidth;
		viewPort.Height = WindowHeight;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		p_D3DDeviceContext->RSSetViewports(1, &viewPort);

		Resize = false;
	}
}

