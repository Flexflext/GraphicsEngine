#include "Material.h"
#include "WICTextureLoader.h" // https://github.com/microsoft/DirectXTex/tree/main/WICTextureLoader
#include "Utils.h"
#include "WICTextureLoader.cpp"

INT Material::Init(IDirect3DDevice9* _p_d3ddevice, LPCTSTR _texturename)
{
	HRESULT hr = CreateWICTextureFromFile(_p_d3ddevice, _texturename, &p_Texture, 0 , WIC_LOADER_MIP_AUTOGEN);
	CheckFailed(hr, 60);

	material.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.Power = 1024.0f; // greater value, smaller the highlights
	//material.Emissive = { 1.0f, 0.0f, 0.0f, 1.0f };

	return 0;
}

void Material::Render(IDirect3DDevice9* _p_d3ddevice)
{
	//Set Sampler State
	_p_d3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); //default: Wrap
	_p_d3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	_p_d3ddevice->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0);
	_p_d3ddevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	_p_d3ddevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC); //default: Point
	_p_d3ddevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC); //default: Point
	_p_d3ddevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16); //default: 1

	//Set Tex
	_p_d3ddevice->SetTexture(0, p_Texture);

	//Set Material
	_p_d3ddevice->SetMaterial(&material);
}

void Material::DeInit()
{
	SafeRelease<IDirect3DTexture9>(p_Texture);
}
