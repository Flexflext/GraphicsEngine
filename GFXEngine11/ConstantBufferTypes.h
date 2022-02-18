#pragma once
#include <DirectXMath.h>
#include <d3d11.h>

using namespace DirectX;

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
