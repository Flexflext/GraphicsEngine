#pragma once
#include <d3d11.h>
#include "Utils.h"
#include <DirectXMath.h>

using namespace DirectX;


class MyTexture
{
public:
	MyTexture(LPCTSTR _texturename, INT _position, bool _shadertype)
	{
		textureName = _texturename;
		pixelShader = _shadertype;
		position = _position;
	}

	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext);
	void Update();
	void DeInit();

private:
	ID3D11ShaderResourceView* p_texture = nullptr;
	ID3D11SamplerState* p_samplerState = nullptr;


	LPCTSTR textureName;
	bool pixelShader;
	INT position;
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
};



