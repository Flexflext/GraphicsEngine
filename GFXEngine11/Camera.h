#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "AllCameras.h"

using namespace DirectX;

class Camera
{
public:
	Camera()
	{
		AllCameras::AddCamera(this);
	}

	INT Init(UINT _screenwidth, UINT _screenheight);
	void Update();
	void DeInit();

	XMFLOAT4X4* GetViewMatrix() { return &viewMatrix; }
	XMFLOAT4X4* GetProjectionMatrix() { return &projectionMatrix; }

private:
	XMFLOAT4X4 viewMatrix = {};
	XMFLOAT4X4 projectionMatrix = {};

};

