//Header to Hold the Different Kinds of Constant Buffer structs
#pragma once
#include <DirectXMath.h>
#include <d3d11.h>

using namespace DirectX;

//Specular Shader Property Data
struct PropertyData
{
	PropertyData(XMFLOAT4 _specularcolor, FLOAT _glossy, FLOAT _specularpower)
	{
		specularColor = _specularcolor;
		glossy = _glossy;
		specularPower = _specularpower;
	}

	XMFLOAT4 specularColor;
	FLOAT glossy;
	FLOAT specularPower;
};

//Matrix Buffer
struct MatrixBuffer
{
	MatrixBuffer()
	{

	}

	MatrixBuffer(XMFLOAT4X4 _wvpmatrix, XMFLOAT4X4 _worldmatrix, XMFLOAT3 _camworldpos)
	{
		camWorldPos = _camworldpos;
		worldMatrix = _worldmatrix;
		worldviewProjectionMatrix = _wvpmatrix;
	}

	XMFLOAT4X4 worldviewProjectionMatrix;
	XMFLOAT4X4 worldMatrix;
	XMFLOAT3 camWorldPos;
};

//Light Data Buffer
struct LightData
{
	XMFLOAT3 LightDirection;
	FLOAT LightIntensity;
	XMFLOAT4 LightDiffuseColor;
	XMFLOAT4 AmbientLight;
};
