#include "TextureLightingProperties.h"
#include <d3dcompiler.h>
#include "WICTextureLoader.cpp"
#include "Camera.h"
#include "AllCameras.h"

INT TextureLightingProperties::InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice, XMFLOAT4X4* _worldmatrix)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;
	p_d3dDevice = _p_d3ddevice;

	//Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut l
	p_matrixBuffer = new ConstantBuffer<MatrixBuffer>(_p_d3ddevice, _p_d3ddevicecontext, 0, false);
	SetMatrices(_worldmatrix);

	//Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.
	INT error = p_abledo->Init(_p_d3ddevice, _p_d3ddevicecontext);
	CheckIntError(error);

	return 0;
}

void TextureLightingProperties::DeinitProperties()
{
	// At vero eos et accusam et justo duo dolores et ea rebum
	p_abledo->DeInit();
}

void TextureLightingProperties::Update()
{
	// At vero eos et accusam et justo duo dolores et ea rebum
	UpdateMatricesBuffer();
	p_abledo->Update();
}

void TextureLightingProperties::SetMatrices(XMFLOAT4X4* _worldmatrix)
{
	//  dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempo
	Camera* cam = AllCameras::GetMainCamera();
	p_worldMatrix = _worldmatrix;
	p_viewMatrix = cam->GetViewMatrix();
	p_projectionMatrix = cam->GetProjectionMatrix();
}

void TextureLightingProperties::UpdateMatricesBuffer()
{
	// At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
	XMMATRIX worldMatrix = XMLoadFloat4x4(p_worldMatrix);
	XMMATRIX viewMatrix = XMLoadFloat4x4(p_viewMatrix);
	XMMATRIX projectionMatrix = XMLoadFloat4x4(p_projectionMatrix);

	XMMATRIX wvpMatrix = XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix); //transpose for column mayor - row mayor problem

	MatrixBuffer temp;

	XMStoreFloat4x4(&(temp.worldviewProjectionMatrix), wvpMatrix);
	XMStoreFloat4x4(&(temp.worldMatrix), XMMatrixTranspose(worldMatrix));
	temp.camWorldPos = AllCameras::GetMainCamera()->gameObject->transform.Position;

	// At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren
	p_matrixBuffer->Update(&temp);
}
