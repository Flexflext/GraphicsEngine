#include "Camera.h"
#include <DirectXMath.h>
#include "Utils.h"

using namespace DirectX;

void Camera::SetMatrices(XMFLOAT3 _forward, XMFLOAT3 _up, XMFLOAT3 _position)
{
	//Set Custom View Matrix
	viewMat = XMMatrixLookToLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_forward.x, _forward.y, _forward.z, 0),
		XMVectorSet(_up.x, _up.y, _up.z, 0)
	);

	XMStoreFloat4x4(&viewMatrix, viewMat);

	//Set Custom Projection Matrix
	projectMat = XMMatrixPerspectiveFovLH(
		XM_PI * 2, // FOV in Radians
		1, //Aspect Ratio
		0.1f, 1000.0f // Near and Far Clip Plane
	);

	XMStoreFloat4x4(&projectionMatrix, projectMat);
}

INT Camera::Init()
{
	//Initialize View and ProjectionMatrix
	ReInitViewMatrix();
	ReInitProjectionMatrix();
	return 0;
}

void Camera::Update()
{
	//Initialize View and ProjectionMatrix
	ReInitViewMatrix();
	ReInitProjectionMatrix();
}

void Camera::DeInit()
{
}

void Camera::ReInitProjectionMatrix()
{
	//Projection Matrix
	projectMat = XMMatrixPerspectiveFovLH(
		XM_PI * 0.3333333f, // FOV in Radians
		(FLOAT)WindowWidth / (FLOAT)WindowHeight, //Aspect Ratio
		0.3f, 1000.0f // Near and Far Clip Plane
	);

	XMStoreFloat4x4(&projectionMatrix, projectMat);
}

void Camera::ReInitViewMatrix()
{
	// View Matrix
	viewMat = XMMatrixLookToLH(XMVectorSet(gameObject->transform.Position.x, gameObject->transform.Position.y, gameObject->transform.Position.z, 0),
							   XMVectorSet(gameObject->transform.LocalForward.x, gameObject->transform.LocalForward.y, gameObject->transform.LocalForward.z, 0),
							   XMVectorSet(gameObject->transform.LocalUp.x, gameObject->transform.LocalUp.y, gameObject->transform.LocalUp.z, 0));

	XMStoreFloat4x4(&viewMatrix, viewMat);
}

INT Camera::AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	Init();

	return 0;
}

void Camera::StartComponent()
{
}

void Camera::UpdateComponent()
{
	Update();
}

void Camera::DeInitComponent()
{
	DeInit();
}
