#include "Light.h"
#include "Utils.h"

INT Light::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext)
{
	//Initialize the Constant Buffer
	p_lightConstantBuffer = new ConstantBuffer<LightData>(_p_d3ddevice, _p_d3ddevicecontext, id, true);

	return 0;
}

void Light::Render()
{
	//Update the Light Direction
	light.LightDirection = this->gameObject->transform.LocalForward;
	//Update the Constant Buffer
	p_lightConstantBuffer->Update(&light);
}

void Light::DeInit()
{
	//Deinit the Constantbuffer
	p_lightConstantBuffer->DeInit();
}

void Light::SetLight(LightData& _light, INT _id)
{
	//Set LightData and ID
	light = _light;
	id = _id;
}

INT Light::AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	//Init
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
