#pragma once
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")

class Material
{
public:
	INT Init(IDirect3DDevice9* _p_d3ddevice, LPCTSTR _texturename);
	void Render(IDirect3DDevice9* _p_d3ddevice);
	void DeInit();

private:
	IDirect3DTexture9* p_Texture;
	D3DMATERIAL9 material = {};
};

