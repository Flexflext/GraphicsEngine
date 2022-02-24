//Cubemap Script to Initialize and Update a Cubemap
#pragma once
#include <d3d11.h>
#include "Utils.h"
#include <DirectXMath.h>

using namespace DirectX;

class MyCubemap
{
public:
	MyCubemap(LPCTSTR _cubemaptex, INT _position, bool _shadertype)
	{
		//Set Path, SHader Type and Position
		cubeMaptextures = _cubemaptex;
		pixelShader = _shadertype;
		position = _position;
	}

	/// <summary>
	/// Initialize the CubeMap
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <returns></returns>
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext);
	/// <summary>
	/// Update the Cubemap Buffer
	/// </summary>
	void Update();
	/// <summary>
	/// Deinitialize the Cubemap
	/// </summary>
	void DeInit();

private:
	//SRV and Sampler State
	ID3D11ShaderResourceView* p_texture = nullptr;
	ID3D11SamplerState* p_samplerState = nullptr;

	//Properties
	LPCTSTR cubeMaptextures;
	bool pixelShader;
	INT position;
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
};

