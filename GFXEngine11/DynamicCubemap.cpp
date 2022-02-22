#include "DynamicCubemap.h"
#include "D3D.h"
#include "Utils.h"

void DynamicCubemap::BuildDynamicCubeMap()
{
	ID3D11Device* p_d3dDevice = D3D::GetInstance()->GetDevice();
	ID3D11DeviceContext* p_d3dDeviceContext = D3D::GetInstance()->GetDeviceContext();

	int size = 256;

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
	HRESULT hr = p_d3dDevice->CreateTexture2D(&texDesc, nullptr, &p_cubeTexture);

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = texDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	rtvDesc.Texture2DArray.ArraySize = 1;
	rtvDesc.Texture2DArray.MipSlice = 0;


	for (size_t i = 0; i < 6; i++)
	{
		rtvDesc.Texture2DArray.FirstArraySlice = i;
		ID3D11RenderTargetView* p_tempRenderTargetView = nullptr;
		HRESULT hr = p_d3dDevice->CreateRenderTargetView(p_cubeTexture, &rtvDesc, &p_tempRenderTargetView);
		p_renderTargetView[i] = *p_tempRenderTargetView;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = -1;

	HRESULT hr = p_d3dDevice->CreateShaderResourceView(p_cubeTexture, &srvDesc, &p_shaderResourceView);
	SafeRelease<ID3D11Texture2D>(p_cubeTexture);

	D3D11_TEXTURE2D_DESC depthTexDesc = {};

}
