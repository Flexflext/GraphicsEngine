#include "MyTexture.h"
#include "WICTextureLoader.h"

INT MyTexture::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;

	//Create Texture RSV
	HRESULT hr = CreateWICTextureFromFile(_p_d3ddevice, textureName, nullptr, &p_texture, 0);
	CheckFailed(hr, 63);


	//Create Sampler State
	D3D11_SAMPLER_DESC desc = {};
	desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	//Create the Sampler State
	hr = _p_d3ddevice->CreateSamplerState(&desc, &p_samplerState);
	CheckFailed(hr, 65);

	return 0;
}

void MyTexture::Update()
{
	//Check if to Update to Pixel or Vertex Shaders
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

void MyTexture::DeInit()
{
	//Release Com Objects
	SafeRelease<ID3D11ShaderResourceView>(p_texture);
	SafeRelease<ID3D11SamplerState>(p_samplerState);
}
