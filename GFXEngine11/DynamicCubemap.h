//Script to try to Implement a Reflection Sphere
#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Component.h"

using namespace DirectX;

class Camera;

class DynamicCubemap : public Component
{
public:
	//Component Object
	DynamicCubemap(GameObject* _go) : Component(_go)
	{
	}

	//Component Override
	INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) override;
	void StartComponent() override;
	void UpdateComponent() override;
	void DeInitComponent() override;

	/// <summary>
	/// Get the Resource View (Cubemap) of this Reflection Sphere
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetReSourceView() { return p_shaderResourceView; };

	/// <summary>
	/// Update the Reflection On this Cubemap
	/// </summary>
	void Update();
private:
	/// <summary>
	/// Build a Dynamic Cubemap Resource View
	/// </summary>
	/// <returns></returns>
	INT BuildDynamicCubeMap();
	/// <summary>
	/// Build theCamera Setup for the Reflection Sphere
	/// </summary>
	/// <param name="_i"></param>
	void BuildCubeMapCameras(int _i);

	//Render Target and Resource Views to Needed to Create a Cubemap
	ID3D11RenderTargetView** pp_renderTargetView = nullptr;
	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;
	ID3D11DepthStencilView* p_depthStencilView = nullptr;

	ID3D11Device* p_d3dDevice = nullptr;
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;

	//Cameras 
	Camera* cubeMapCameras[6];

	//Size of the Created Picture 256*256
	int size = 256;
};

