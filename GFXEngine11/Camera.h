#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "AllCameras.h"
#include "Component.h"

using namespace DirectX;

class Camera : public Component
{
public:
	Camera(GameObject* _go, EComponentTypes _type) : Component(_go, _type)
	{
		AllCameras::AddCamera(this);
	}

	INT Init();
	void Update();
	void DeInit();

	INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) override;
	void StartComponent();
	void UpdateComponent();
	void DeInitComponent();

	XMFLOAT4X4* GetViewMatrix() { return &viewMatrix; }
	XMFLOAT4X4* GetProjectionMatrix() { return &projectionMatrix; }

private:
	XMFLOAT4X4 viewMatrix = {};
	XMFLOAT4X4 projectionMatrix = {};

	XMMATRIX viewMat;
};

