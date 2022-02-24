//Specular Shader Properties
#pragma once
#include "MaterialProperties.h"
#include <DirectXMath.h>
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "MyTexture.h"

using namespace DirectX;

class SpecularLightingProperties : public MaterialProperties
{
public:
	SpecularLightingProperties(LPCTSTR _texturename, FLOAT _glossy, XMFLOAT4 _specularcolor, FLOAT _specularpower)
	{
		//Set Properties
		glossy = _glossy;
		specularPower = _specularpower;
		specularColor = _specularcolor;
		p_albedo = new MyTexture(_texturename, 0, true);

		//Set the Material Type
		materialType = EMaterials::SpecularLight;
	}


	//MaterialProperties Override
	INT InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice, XMFLOAT4X4* _worldmatrix) override;
	void DeinitProperties() override;
	void Update() override;

private:
	/// <summary>
	/// Set Matrices to Constant Buffer
	/// </summary>
	/// <param name="_worldmatrix"></param>
	void SetMatrices(XMFLOAT4X4* _worldmatrix);
	/// <summary>
	/// Update Matrices Buffer
	/// </summary>
	void UpdateMatricesBuffer();

	//Properties
	MyTexture* p_albedo = nullptr;
	XMFLOAT4 specularColor;
	FLOAT glossy;
	FLOAT specularPower;
	ConstantBuffer<PropertyData>* p_propertyBuffer = nullptr;
	ConstantBuffer<MatrixBuffer>* p_matrixBuffer = nullptr;

	//Matrices
	XMFLOAT4X4* p_worldMatrix = nullptr;
	XMFLOAT4X4* p_viewMatrix = nullptr;
	XMFLOAT4X4* p_projectionMatrix = nullptr;

};

