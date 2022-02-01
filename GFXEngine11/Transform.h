#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
public:
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;

	INT Init();
	void Update();
	INT DeInit();
	Transform()
	{
		Scale.x = 1;
		Scale.y = 1;
		Scale.z = 1;
	}

	void SetPosition(FLOAT _x, FLOAT _y, FLOAT _z);
	void SetRotation(FLOAT _x, FLOAT _y, FLOAT _z);
	void SetScale(FLOAT _x, FLOAT _y, FLOAT _z);

	XMFLOAT4X4 WorldMatrix = {};
};

