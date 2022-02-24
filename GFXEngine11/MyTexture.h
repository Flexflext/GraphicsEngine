// Script for a Texture that ist passed to the Shader
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
		//Set Texture Name, the Shader Type that it will be passed to and the Register Position
		textureName = _texturename;
		pixelShader = _shadertype;
		position = _position;
	}

	/// <summary>
	/// Initialize the Shader Texture and Texture Sampler
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <returns></returns>
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext);
	/// <summary>
	/// Updates the Shader Ressource View
	/// </summary>
	void Update();
	/// <summary>
	/// Deinitialize the Texture and Sampler
	/// </summary>
	void DeInit();

private:
	//Sampler and Ressource View
	ID3D11ShaderResourceView* p_texture = nullptr;
	ID3D11SamplerState* p_samplerState = nullptr;


	LPCTSTR textureName;
	bool pixelShader;
	INT position;
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
};



