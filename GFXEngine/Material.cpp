#include "Material.h"
#include "WICTextureLoader.cpp" // https://github.com/microsoft/DirectXTex/tree/main/WICTextureLoader
#include "Utils.h"

INT Material::Init(IDirect3DDevice9* _p_d3ddevice, LPCTSTR _texturename)
{
	HRESULT hr = CreateWICTextureFromFile(_p_d3ddevice, _texturename, &p_texture);
	CheckFailed(hr, 60);

	return 0;
}

void Material::Render(IDirect3DDevice9* _p_d3ddevice)
{
	_p_d3ddevice->SetTexture(0, p_texture);
}

void Material::DeInit()
{
	SafeRelease<IDirect3DTexture9>(p_texture);
}
