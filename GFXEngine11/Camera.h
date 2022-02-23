// Script for a Camera Component
#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "AllCameras.h"
#include "Component.h"

using namespace DirectX;

class Camera : public Component
{
public:
	Camera(GameObject* _go) : Component(_go)
	{
		//Add Camera to Camera Holder
		AllCameras::AddCamera(this);
	}

	/// <summary>
	/// Set Custom Matrices
	/// </summary>
	/// <param name="_forward"></param>
	/// <param name="_up"></param>
	/// <param name="_position"></param>
	void SetMatrices(XMFLOAT3 _forward, XMFLOAT3 _up, XMFLOAT3 _position);

	/// <summary>
	/// Initialize the Cameras Matrices
	/// </summary>
	/// <returns></returns>
	INT Init();
	/// <summary>
	/// Update the Cameras Matrices
	/// </summary>
	void Update();
	/// <summary>
	/// DeInitialize the Camera
	/// </summary>
	void DeInit();
	/// <summary>
	/// ReInitialize the Projection Matrices
	/// </summary>
	void ReInitProjectionMatrix();
	/// <summary>
	/// ReInitialize the View Matrix
	/// </summary>
	void ReInitViewMatrix();


	// --> Component MEthod Overrides
	INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) override;
	void StartComponent();
	void UpdateComponent();
	void DeInitComponent();

	/// <summary>
	/// Get the View Matrix of the Camera
	/// </summary>
	/// <returns></returns>
	XMFLOAT4X4* GetViewMatrix() { return &viewMatrix; }
	/// <summary>
	/// Get the Projection Matrix of the Camera
	/// </summary>
	/// <returns></returns>
	XMFLOAT4X4* GetProjectionMatrix() { return &projectionMatrix; }

private:
	XMFLOAT4X4 viewMatrix = {};
	XMFLOAT4X4 projectionMatrix = {};

	XMMATRIX viewMat;
	XMMATRIX projectMat;
};

