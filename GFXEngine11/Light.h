#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Light
{
public:
	struct  LightData 
	{
		//XMFLOAT3 LightDirection;
		//FLOAT Padding; // because of 16 byte alignment
		//XMFLOAT4 LightDiffuseColor;
		//FLOAT LightIntensity;
		//XMFLOAT3 Padding2; // because of 16 byte alignment

		XMFLOAT3 LightDirection;
		FLOAT LightIntensity;
		XMFLOAT4 LightDiffuseColor;
	};


	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, LightData &_light, INT _id = 0);
	void Render();
	void DeInit();

private:
	INT id = 0;
	LightData light = {};
	ID3D11Buffer* p_lightBuffer = nullptr;

	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
};

