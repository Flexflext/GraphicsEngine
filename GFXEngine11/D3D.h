#pragma once
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

class D3D
{
public:
	INT Init(HWND _hwnd, UINT _width, UINT _height, BOOL _fullscreen);
	void BeginScene(FLOAT _red = 0.0f, FLOAT _green = 0.0f, FLOAT _blue = 0.0f);
	void EndScene();
	void DeInit();

	void OnResize();

	ID3D11Device* GetDevice() { return p_D3DDevice; }
	ID3D11DeviceContext* GetDeviceContext() { return p_D3DDeviceContext; }

private:
	ID3D11Device* p_D3DDevice = nullptr; // creating objects, e.g. vertex buffer
	ID3D11DeviceContext* p_D3DDeviceContext = nullptr; // handling render pipeline, e.g. set resopurces or draw call
	IDXGISwapChain* p_DXGISwapChain = nullptr; // hold refernces to front and back buffer and swap them
	ID3D11RenderTargetView* p_RenderTargetView = nullptr; // Decribe the Target the render pipeline will render in, e.g. back buffer
	ID3D11DepthStencilView* p_depthStencilView = nullptr; // hold ref to depth and stencil buffer texture
	ID3D11RasterizerState* p_rasterizerState = nullptr; // set up rasterizer stage
};

