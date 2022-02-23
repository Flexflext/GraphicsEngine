#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Component.h"

using namespace DirectX;

class Camera;

class DynamicCubemap : public Component
{
public:
	DynamicCubemap(GameObject* _go) : Component(_go)
	{
	}

	INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) override;
	void StartComponent() override;
	void UpdateComponent() override;
	void DeInitComponent() override;

	ID3D11ShaderResourceView* GetReSourceView() { return p_shaderResourceView; };

	void Update();
private:
	INT BuildDynamicCubeMap();
	void BuildCubeMapCameras(int _i);

	void DeInit();

	ID3D11RenderTargetView** pp_renderTargetView = nullptr;
	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;
	ID3D11DepthStencilView* p_depthStencilView = nullptr;

	ID3D11Device* p_d3dDevice = nullptr;
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;


	Camera* cubeMapCameras[6];
	int size = 256;
};

