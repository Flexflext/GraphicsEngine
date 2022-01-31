#include "Light.h"
#include "Utils.h"

INT Light::Init(ID3D11Device* _p_d3ddevice, LightData& _light, INT _id)
{
	light = _light;
	id = _id;

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

void Light::Render(ID3D11DeviceContext* _p_d3ddevicecontext)
{
	_p_d3ddevicecontext->PSSetConstantBuffers(id, 1, &p_lightBuffer);
}

void Light::DeInit()
{
	SafeRelease<ID3D11Buffer>(p_lightBuffer);
}
