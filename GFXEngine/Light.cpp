#include "Light.h"

INT Light::Init(D3DLIGHT9& _light, INT _id)
{
	light = _light;
	id = _id;

	return 0;
}

void Light::Render(IDirect3DDevice9* _p_D3DDevice)
{
	_p_D3DDevice->SetLight(id, &light);
	_p_D3DDevice->LightEnable(id, TRUE);
}

void Light::DeInit()
{
}
