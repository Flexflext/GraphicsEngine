#include "DynamicCubemap.h"
#include "D3D.h"
#include "Utils.h"
#include "Camera.h"

INT DynamicCubemap::AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	BuildDynamicCubeMap();

	return 0;
}

void DynamicCubemap::StartComponent()
{
}

void DynamicCubemap::UpdateComponent()
{
}

void DynamicCubemap::DeInitComponent()
{
}

INT DynamicCubemap::BuildDynamicCubeMap()
{
	p_d3dDevice = D3D::GetInstance()->GetDevice();
	p_d3dDeviceContext = D3D::GetInstance()->GetDeviceContext();

	//Create Texture Description for CubeMap Texture
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = size;
	texDesc.Height = size;
	texDesc.MipLevels = 0;
	texDesc.ArraySize = 6;
	texDesc.SampleDesc = { 1,0 };
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	texDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE | D3D11_RESOURCE_MISC_GENERATE_MIPS;

	ID3D11Texture2D* p_cubeTexture = nullptr;
	// Create Cube Map Texture
	HRESULT hr = p_d3dDevice->CreateTexture2D(&texDesc, nullptr, &p_cubeTexture);
	CheckFailed(hr, 1);

	//Create RTV Description
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = texDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	rtvDesc.Texture2DArray.ArraySize = 1;
	rtvDesc.Texture2DArray.MipSlice = 0;

	//Create Render Target PP
	pp_renderTargetView = new ID3D11RenderTargetView * [6];

	for (size_t i = 0; i < 6; i++)
	{
		//-> Set Array Slice
		rtvDesc.Texture2DArray.FirstArraySlice = i;
		//-> Set the Render Target View
		HRESULT hr = p_d3dDevice->CreateRenderTargetView(p_cubeTexture, &rtvDesc, &pp_renderTargetView[i]);
		CheckFailed(hr, 1);
	}

	//Setup for Shader Resource View
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = -1;

	//Create the Resource View
	hr = p_d3dDevice->CreateShaderResourceView(p_cubeTexture, &srvDesc, &p_shaderResourceView);
	CheckFailed(hr, 1);
	SafeRelease<ID3D11Texture2D>(p_cubeTexture);

	//Setup Depth Texture
	D3D11_TEXTURE2D_DESC depthTexDesc = {};
	depthTexDesc.Width = size;
	depthTexDesc.Height = size;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.SampleDesc = { 1,0 };
	depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;

	ID3D11Texture2D* p_depthTex = nullptr;
	//Create the Texture
	hr = p_d3dDevice->CreateTexture2D(&depthTexDesc, nullptr, &p_depthTex);
	CheckFailed(hr, 1);

	//Setup DSV Description
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = depthTexDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	//Create Depth Stencil View
	hr = p_d3dDevice->CreateDepthStencilView(p_depthTex, &dsvDesc, &p_depthStencilView);
	CheckFailed(hr, 1);
	SafeRelease<ID3D11Texture2D>(p_depthTex);
	
}

void DynamicCubemap::BuildCubeMapCameras(int _i)
{
	//Set Position
	XMFLOAT3 center = { this->gameObject->transform.Position.x, this->gameObject->transform.Position.y, this->gameObject->transform.Position.z };

	//Forward Directions
	XMFLOAT3 forwards[]
	{
		{center.x + 1, center.y, center.z},
		{center.x - 1, center.y, center.z},
		{center.x, center.y + 1, center.z},
		{center.x, center.y - 1, center.z},
		{center.x, center.y, center.z + 1},
		{center.x, center.y, center.z - 1},
	};

	//Up Directions
	XMFLOAT3 ups[]
	{
		{0,1,0},
		{0,1,0},
		{0,0,-1},
		{0,0,1},
		{0,1,0},
		{0,1,0},
	};

	//Set Camera
	cubeMapCameras[_i] = new Camera(gameObject);
	//Set Matrices of Camera
	cubeMapCameras[_i]->SetMatrices(forwards[_i], ups[_i], center);
}

void DynamicCubemap::Update()
{
	//-> Not Working

	/*D3D11_VIEWPORT viewPort = {};
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = size;
	viewPort.Height = size;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	p_d3dDeviceContext->RSSetViewports(1, &viewPort);

	FLOAT backgroundColor[] = { 1, 1, 1, 1.0f };

	for (size_t i = 0; i < 6; i++)
	{
		D3D11_VIEWPORT viewPort = {};
		viewPort.TopLeftX = 0.0f;
		viewPort.TopLeftY = 0.0f;
		viewPort.Width = size;
		viewPort.Height = size;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;

		p_d3dDeviceContext->RSSetViewports(1 + i, &viewPort);

		BuildCubeMapCameras(i);

		p_d3dDeviceContext->ClearRenderTargetView(pp_renderTargetView[i], backgroundColor);
		p_d3dDeviceContext->ClearDepthStencilView(p_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		p_d3dDeviceContext->OMSetRenderTargets(1, &pp_renderTargetView[i], p_depthStencilView);
	}*/
}
