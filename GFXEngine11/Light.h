//DirectionalLight Component
#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Component.h"
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"

using namespace DirectX;

class Light : public Component
{
public:
	Light(GameObject* _go) : Component(_go) {}

	/// <summary>
	/// Initialize the Light
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <returns></returns>
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext);
	/// <summary>
	/// Render the LightData
	/// </summary>
	void Render();
	/// <summary>
	/// Deinit LightData
	/// </summary>
	void DeInit();
	/// <summary>
	/// Set the initial LightData
	/// </summary>
	/// <param name="_light"></param>
	/// <param name="_id"></param>
	void SetLight(LightData& _light, INT _id = 0);

	//Component Override
	INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) override;
	void StartComponent() override;
	void UpdateComponent() override;
	void DeInitComponent() override;

private:
	INT id = 0;
	LightData light = {};

	//Light Constant Data
	ConstantBuffer<LightData>* p_lightConstantBuffer = nullptr;
};

