#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	INT Init(UINT _screenwidth, UINT _screenheight);
	void Update(FLOAT _dt);
	void DeInit();

	XMFLOAT4X4* GetViewMatrix() { return &viewMatrix; }
	XMFLOAT4X4* GetProjectionMatrix() { return &projectionMatrix; }

private:
	XMFLOAT4X4 viewMatrix = {};
	XMFLOAT4X4 projectionMatrix = {};

};

