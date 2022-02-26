#include "MyCubemap.h"
#include "WICTextureLoader.h"
#include <d3d11.h>
#include <D3DX11.h>
#include "ReflectionProbeManager.h"
#include "DynamicCubemap.h"

INT MyCubemap::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;

	
	ID3D11Texture2D* p_cubemap = nullptr;
	HRESULT hr;

	D3DX11_IMAGE_LOAD_INFO loadInfo = {};
	loadInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	//Load a Cubemap from a File
	hr = D3DX11CreateTextureFromFile(_p_d3ddevice, cubeMaptextures, &loadInfo, nullptr, (ID3D11Resource**)&p_cubemap, &hr);
	CheckFailed(hr, 63);


	//Set Nessesary Description to Create Cubemap
	D3D11_TEXTURE2D_DESC textureDesc;
	p_cubemap->GetDesc(&textureDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.TextureCube.MipLevels = textureDesc.MipLevels;
	srvDesc.TextureCube.MostDetailedMip = 0;

	// Set the Shader Resource View
	hr = _p_d3ddevice->CreateShaderResourceView(p_cubemap, &srvDesc, &p_texture);
	SafeRelease<ID3D11Texture2D>(p_cubemap);


	//Create Sampler State
	D3D11_SAMPLER_DESC desc = {};

	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	hr = _p_d3ddevice->CreateSamplerState(&desc, &p_samplerState);
	CheckFailed(hr, 65);

	return 0;
}

void MyCubemap::Update()
{
	//Update Texture and Sampler
	if (pixelShader)
	{
		p_d3dDeviceContext->PSSetShaderResources(position, 1, &p_texture);
		p_d3dDeviceContext->PSSetSamplers(position, 1, &p_samplerState);
	}
	else
	{
		p_d3dDeviceContext->VSSetShaderResources(position, 1, &p_texture);
		p_d3dDeviceContext->VSSetSamplers(position, 1, &p_samplerState);
	}
}

void MyCubemap::DeInit()
{
	//Deinitialize the Com Objects
	SafeRelease<ID3D11ShaderResourceView>(p_texture);
	SafeRelease<ID3D11SamplerState>(p_samplerState);
}