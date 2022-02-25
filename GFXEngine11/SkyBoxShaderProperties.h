#pragma once
#include "MaterialProperties.h"
#include "MyCubemap.h"

class SkyBoxShaderProperties : public MaterialProperties
{
public:
	SkyBoxShaderProperties(LPCTSTR _skyboxpath) 
	{
		materialType = EMaterials::SkyBox;
		p_skyBox = new MyCubemap(_skyboxpath, 0, true);
	}

	INT InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice, XMFLOAT4X4* _worldmatrix) override;
	void Update() override;
	void DeinitProperties() override;

private:
	/// <summary>
	/// Set Matrices
	/// </summary>
	/// <param name="_worldmatrix"></param>
	void SetMatrices(XMFLOAT4X4* _worldmatrix);
	/// <summary>
	/// Update Matrices
	/// </summary>
	void UpdateMatricesBuffer();

	MyCubemap* p_skyBox = nullptr;
	ConstantBuffer<MatrixBuffer>* p_matrixBuffer = nullptr;
	ID3D11DepthStencilState* p_depthStencilState = nullptr;

	//Matrices
	XMFLOAT4X4* p_worldMatrix = nullptr;
	XMFLOAT4X4* p_viewMatrix = nullptr;
	XMFLOAT4X4* p_projectionMatrix = nullptr;
};

