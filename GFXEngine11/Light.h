#pragma once
#include <d3d9.h>

class Light
{
public:
	INT Init(D3DLIGHT9 &_light, INT _id = 0);
	void Render(IDirect3DDevice9* _p_D3DDevice);
	void DeInit();

private:
	INT id = 0;
	D3DLIGHT9 light = {};
};

