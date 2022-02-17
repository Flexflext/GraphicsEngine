#include "SpecularLightingProperties.h"
#include <d3dcompiler.h>
#include "WICTextureLoader.cpp"
#include <d3d11.h>
#include "Camera.h"
#include "AllCameras.h"
#include "comdef.h"


INT SpecularLightingProperties::InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;
	p_d3dDevice = _p_d3ddevice;

	//Create Texture
	HRESULT hr = CreateWICTextureFromFile(_p_d3ddevice, textureName, nullptr, &p_texture, 0);
	CheckFailed(hr, 63);



	D3D11_BUFFER_DESC bufferDesc = {};

	bufferDesc.ByteWidth = sizeof(PropertyData);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = _p_d3ddevice->CreateBuffer(&bufferDesc, nullptr, &p_propBuffer);
	CheckFailed(hr, 62);



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

void SpecularLightingProperties::DeinitProperties()
{
	SafeRelease<ID3D11ShaderResourceView>(p_texture);
	SafeRelease<ID3D11SamplerState>(p_samplerState);
}

void SpecularLightingProperties::Update()
{
	//Set Tex and Sampler State
	D3D11_MAPPED_SUBRESOURCE* data = new D3D11_MAPPED_SUBRESOURCE();
	HRESULT hr = p_d3dDeviceContext->Map(p_propBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, data);

	p_propData = static_cast<PropertyData*>(data->pData);

	p_d3dDeviceContext->Unmap(p_propBuffer, 0);

	p_propData->glossy = glossy;
	p_propData->specularColor = specularColor;
	p_propData->specularPower = specularPower;


	p_d3dDeviceContext->PSSetConstantBuffers(1, 1, &p_propBuffer);

	p_d3dDeviceContext->PSSetShaderResources(0, 1, &p_texture);
	p_d3dDeviceContext->PSSetSamplers(0, 1, &p_samplerState);
}