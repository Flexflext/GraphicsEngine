#include "Camera.h"
#include <DirectXMath.h>

using namespace DirectX;

INT Camera::Init(UINT _screenwidth, UINT _screenheight)
{
	// View Matrix
	XMMATRIX viewMat = XMMatrixLookToLH(
		XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f), //Pos
		XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), //Forward
		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) //Up
	);

	XMStoreFloat4x4(&viewMatrix, viewMat);

	//Projection Matrix

	XMMATRIX projectMat = XMMatrixPerspectiveFovLH(
		XM_PI * 0.3333333f, // FOV in Radians
		(FLOAT)_screenwidth / (FLOAT)_screenheight, //Aspect Ratio
		0.3f, 1000.0f // Near and Far Clip Plane
	);

	XMStoreFloat4x4(&projectionMatrix, projectMat);

	return 0;
}

void Camera::Update()
{
	

}

void Camera::DeInit()
{
}
