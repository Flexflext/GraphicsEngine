#include "SkyBoxShaderProperties.h"
#include "Camera.h"

INT SkyBoxShaderProperties::InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice, XMFLOAT4X4* _worldmatrix)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;
	p_d3dDevice = _p_d3ddevice;

	D3D11_DEPTH_STENCIL_DESC depthDesc = {};
	depthDesc.DepthEnable = true;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	HRESULT hr = p_d3dDevice->CreateDepthStencilState(&depthDesc, &p_depthStencilState);
	CheckFailed(hr, 101);

	//initlaize Properties
	p_matrixBuffer = new ConstantBuffer<MatrixBuffer>(_p_d3ddevice, _p_d3ddevicecontext, 0, false);

	INT error = p_skyBox->Init(_p_d3ddevice, _p_d3ddevicecontext);
	CheckIntError(error);

	//Set Matrices
	SetMatrices(_worldmatrix);

    return 0;
}

void SkyBoxShaderProperties::Update()
{
	p_d3dDeviceContext->OMSetDepthStencilState(p_depthStencilState, 0);

	UpdateMatricesBuffer();
	p_skyBox->Update();
}

void SkyBoxShaderProperties::DeinitProperties()
{
	p_matrixBuffer->DeInit();
	p_skyBox->DeInit();
}

void SkyBoxShaderProperties::SetMatrices(XMFLOAT4X4* _worldmatrix)
{
	//Set the Matrices
	Camera* cam = AllCameras::GetMainCamera();
	p_worldMatrix = _worldmatrix;
	p_viewMatrix = cam->GetViewMatrix();
	p_projectionMatrix = cam->GetProjectionMatrix();
}

void SkyBoxShaderProperties::UpdateMatricesBuffer()
{
	//Set Matrices
	XMMATRIX worldMatrix = XMLoadFloat4x4(p_worldMatrix);
	XMMATRIX viewMatrix = XMLoadFloat4x4(p_viewMatrix);
	XMMATRIX projectionMatrix = XMLoadFloat4x4(p_projectionMatrix);

	//Transpose Matrices
	XMMATRIX wvpMatrix = XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix); //transpose for column mayor - row mayor problem

	MatrixBuffer temp;

	//Store XMMatrix in XMFLOAt4x4
	XMStoreFloat4x4(&(temp.worldviewProjectionMatrix), wvpMatrix);
	XMStoreFloat4x4(&(temp.worldMatrix), XMMatrixTranspose(worldMatrix));
	temp.camWorldPos = AllCameras::GetMainCamera()->gameObject->transform.Position;

	//Update Buffer
	p_matrixBuffer->Update(&temp);
}
