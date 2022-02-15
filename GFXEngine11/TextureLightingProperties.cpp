#include "TextureLightingProperties.h"
#include <d3dcompiler.h>
#include "WICTextureLoader.cpp"

INT TextureLightingProperties::InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;
	p_d3dDevice = _p_d3ddevice;

	//Create Texture
	HRESULT hr = CreateWICTextureFromFile(_p_d3ddevice, textureName, nullptr, &p_texture, 0);
	CheckFailed(hr, 63);


	//Create Sampler State
	D3D11_SAMPLER_DESC desc = {};

	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	hr = _p_d3ddevice->CreateSamplerState(&desc, &p_samplerState);
	CheckFailed(hr, 65);
}

void TextureLightingProperties::DeinitProperties()
{
	SafeRelease<ID3D11ShaderResourceView>(p_texture);
	SafeRelease<ID3D11SamplerState>(p_samplerState);
}

void TextureLightingProperties::Update()
{
	////Set Tex and Sampler State
	p_d3dDeviceContext->PSSetShaderResources(0, 1, &p_texture);
	p_d3dDeviceContext->PSSetShaderResources(1, 1, &p_sectexture);
	p_d3dDeviceContext->PSSetSamplers(0, 1, &p_samplerState);
}
