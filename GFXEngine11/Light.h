#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Component.h"

using namespace DirectX;

class Light : public Component
{
public:
	struct LightData 
	{
		// because of 16 byte alignment
		XMFLOAT3 LightDirection;
		FLOAT LightIntensity;
		XMFLOAT4 LightDiffuseColor;
		XMFLOAT4 AmbientLight;
	};

	Light(GameObject* _go) : Component(_go) {}

	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext);
	void Render();
	void DeInit();
	void SetLight(LightData& _light, INT _id = 0);

	//Component Override
	INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) override;
	void StartComponent() override;
	void UpdateComponent() override;
	void DeInitComponent() override;

private:
	INT id = 0;
	LightData light = {};
	ID3D11Buffer* p_lightBuffer = nullptr;

	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
};

