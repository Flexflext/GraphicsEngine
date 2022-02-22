#include "ReflectionShaderProperties.h"
#include <d3dcompiler.h>
#include "WICTextureLoader.cpp"
#include <d3d11.h>
#include "Camera.h"
#include "AllCameras.h"
#include "comdef.h"


INT ReflectionShaderProperties::InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice, XMFLOAT4X4* _worldmatrix)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;
	p_d3dDevice = _p_d3ddevice;

	p_propertyBuffer = new ConstantBuffer<PropertyData>(_p_d3ddevice, _p_d3ddevicecontext, 1, true, new PropertyData(specularColor, glossy, specularPower));
	p_matrixBuffer = new ConstantBuffer<MatrixBuffer>(_p_d3ddevice, _p_d3ddevicecontext, 0, false);
	INT error = p_albedo->Init(_p_d3ddevice, _p_d3ddevicecontext);
	CheckIntError(error);

	error = p_normal->Init(_p_d3ddevice, _p_d3ddevicecontext);
	CheckIntError(error);

	error = p_reflect->Init(_p_d3ddevice, _p_d3ddevicecontext);
	CheckIntError(error);

	SetMatrices(_worldmatrix);

	ID3D11Texture2D* cubeMapTexture = nullptr;
	

	return 0;
}

void ReflectionShaderProperties::DeinitProperties()
{
	p_albedo->DeInit();
	p_normal->DeInit();
	p_reflect->DeInit();
	p_propertyBuffer->DeInit();
	p_matrixBuffer->DeInit();
}

void ReflectionShaderProperties::Update()
{
	UpdateMatricesBuffer();

	p_albedo->Update();
	p_normal->Update();
	p_reflect->Update();
}

void ReflectionShaderProperties::SetMatrices(XMFLOAT4X4* _worldmatrix)
{
	Camera* cam = AllCameras::GetMainCamera();
	p_worldMatrix = _worldmatrix;
	p_viewMatrix = cam->GetViewMatrix();
	p_projectionMatrix = cam->GetProjectionMatrix();
}

void ReflectionShaderProperties::UpdateMatricesBuffer()
{
	XMMATRIX worldMatrix = XMLoadFloat4x4(p_worldMatrix);
	XMMATRIX viewMatrix = XMLoadFloat4x4(p_viewMatrix);
	XMMATRIX projectionMatrix = XMLoadFloat4x4(p_projectionMatrix);

	XMMATRIX wvpMatrix = XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix); //transpose for column mayor - row mayor problem

	MatrixBuffer temp;

	XMStoreFloat4x4(&(temp.worldviewProjectionMatrix), wvpMatrix);
	XMStoreFloat4x4(&(temp.worldMatrix), XMMatrixTranspose(worldMatrix));
	temp.camWorldPos = AllCameras::GetMainCamera()->gameObject->transform.Position;

	p_matrixBuffer->Update(new MatrixBuffer(temp.worldviewProjectionMatrix, temp.worldMatrix, temp.camWorldPos));
}