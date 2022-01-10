#pragma once
#include <d3d9.h>

class Camera
{
public:
	INT Init(UINT _screenwidth, UINT _screenheight);
	void Render(IDirect3DDevice9* _p_D3DDevice);
	void DeInit();

private:
	D3DMATRIX viewMatrix = {};
	D3DMATRIX projectionMatrix = {};

};

