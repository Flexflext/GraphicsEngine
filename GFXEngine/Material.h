#pragma once
#include <d3d9.h>

class Material
{
public:
	INT Init(IDirect3DDevice9* _p_d3ddevice, LPCTSTR _texturename);
	void Render(IDirect3DDevice9* _p_d3ddevice);
	void DeInit();

private:
	IDirect3DTexture9* p_texture;
};

