#pragma once
#include "Component.h"
#include "Camera.h"

class FreeLookCam : public Component
{
public:
	FreeLookCam(GameObject* _go, EComponentTypes _type) : Component(_go, _type) {};

	INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) override;
	void StartComponent() override;
	void UpdateComponent() override;
	void DeInitComponent() override;


private:
	FLOAT* p_deltaTime = nullptr;
	Camera* p_cam = nullptr;
	FLOAT camMovementSpeed = 10;
	FLOAT camRotationSpeed = 25;
};

