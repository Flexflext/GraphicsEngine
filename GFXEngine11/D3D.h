//Script to Create a Handle to DirectX
#pragma once
#include <d3d11.h>

//-> Import D3D11 Library
#pragma comment(lib, "d3d11.lib")

class D3D
{
public:
	//Singelton Logic
	D3D(D3D& other) = delete;
	void operator=(const D3D&) = delete;

	/// <summary>
	/// Get Instance of the DirectX Singelton
	/// </summary>
	/// <returns>DirectX Instance</returns>
	static D3D* GetInstance();

	/// <summary>
	/// Initialize the DirectX Handle
	/// </summary>
	/// <param name="_hwnd"></param>
	/// <param name="_width"></param>
	/// <param name="_height"></param>
	/// <param name="_fullscreen"></param>
	/// <returns>Error Code</returns>
	INT Init(HWND _hwnd, UINT _width, UINT _height, BOOL _fullscreen);
	/// <summary>
	/// Begins the DirectX Scene
	/// </summary>
	/// <param name="_red"></param>
	/// <param name="_green"></param>
	/// <param name="_blue"></param>
	void BeginScene(FLOAT _red = 0.0f, FLOAT _green = 0.0f, FLOAT _blue = 0.0f);
	/// <summary>
	/// Ends the DirectX Scene
	/// </summary>
	void EndScene();
	/// <summary>
	/// Deinitialize the DirectX Handle
	/// </summary>
	void DeInit();
	/// <summary>
	/// On Resize Method to Resize the DirectX Handle
	/// </summary>
	void OnResize();

	/// <summary>
	/// Get the DirectX Device
	/// </summary>
	/// <returns></returns>
	ID3D11Device* GetDevice() { return p_D3DDevice; }
	/// <summary>
	/// Get the DirectX Device Context
	/// </summary>
	/// <returns></returns>
	ID3D11DeviceContext* GetDeviceContext() { return p_D3DDeviceContext; }

private:
	ID3D11Device* p_D3DDevice = nullptr; // creating objects, e.g. vertex buffer
	ID3D11DeviceContext* p_D3DDeviceContext = nullptr; // handling render pipeline, e.g. set resources or draw call
	IDXGISwapChain* p_DXGISwapChain = nullptr; // hold refernces to front and back buffer and swap them
	ID3D11RenderTargetView* p_RenderTargetView = nullptr; // Decribe the Target the render pipeline will render in, e.g. back buffer
	ID3D11DepthStencilView* p_depthStencilView = nullptr; // hold ref to depth and stencil buffer texture
	ID3D11RasterizerState* p_rasterizerState = nullptr; // set up rasterizer stage

	//Singelton Instance
	static D3D* Instance;

	//Private Constructor -> no public Initialization
	D3D()
	{

	}

};

