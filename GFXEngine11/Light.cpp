#include "Light.h"
#include "Utils.h"

INT Light::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(LightData);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = &light;

	HRESULT hr = _p_d3ddevice->CreateBuffer(&desc, &data, &p_lightBuffer);
	CheckFailed(hr, 70);

	return 0;
}

void Light::Render()
{
	p_d3dDeviceContext->PSSetConstantBuffers(id, 1, &p_lightBuffer);
}

void Light::DeInit()
{
	SafeRelease<ID3D11Buffer>(p_lightBuffer);
	SafeRelease<ID3D11DeviceContext>(p_d3dDeviceContext);
}

void Light::SetLight(LightData& _light, INT _id)
{
	light = _light;
	id = _id;
}

INT Light::AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	INT error = Init(_p_d3ddevice, _p_d3ddevicecontext);
	CheckIntError(error);
}

void Light::StartComponent()
{
}

void Light::UpdateComponent()
{
	Render();
}

void Light::DeInitComponent()
{
	DeInit();
}
