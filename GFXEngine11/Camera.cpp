#include "Camera.h"
#include <DirectXMath.h>
#include "Utils.h"

using namespace DirectX;

INT Camera::Init()
{
	// View Matrix
	viewMat = XMMatrixInverse(nullptr, XMMatrixMultiply(XMMatrixInverse(nullptr, gameObject->transform.RotationMatrix), gameObject->transform.TranslationMatrix));

	XMStoreFloat4x4(&viewMatrix, viewMat);

	//Projection Matrix
	XMMATRIX projectMat = XMMatrixPerspectiveFovLH(
		XM_PI * 0.3333333f, // FOV in Radians
		(FLOAT)WindowWidth / (FLOAT)WindowHeight, //Aspect Ratio
		0.3f, 1000.0f // Near and Far Clip Plane
	);

	XMStoreFloat4x4(&projectionMatrix, projectMat);

	return 0;
}

void Camera::Update()
{
	viewMat = XMMatrixInverse(nullptr, XMMatrixMultiply(XMMatrixInverse(nullptr, gameObject->transform.RotationMatrix),  gameObject->transform.TranslationMatrix));

	XMStoreFloat4x4(&viewMatrix, viewMat);
}

void Camera::DeInit()
{
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
