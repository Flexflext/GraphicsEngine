#pragma once
#include "MaterialProperties.h"
#include <DirectXMath.h>
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "MyTexture.h"

using namespace DirectX;

class NormalShaderProperties : public MaterialProperties
{
public:
	NormalShaderProperties(LPCTSTR _texturename, LPCTSTR _normaltexturename, FLOAT _glossy, XMFLOAT4 _specularcolor, FLOAT _specularpower)
	{
		glossy = _glossy;
		specularPower = _specularpower;
		specularColor = _specularcolor;
		materialType = EMaterials::NormalShader;

		p_albedo = new MyTexture(_texturename, 0, true);
		p_normal = new MyTexture(_normaltexturename, 1, true);
	}



	INT InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice, XMFLOAT4X4* _worldmatrix) override;
	void DeinitProperties() override;
	void Update() override;

private:
	void SetMatrices(XMFLOAT4X4* _worldmatrix);
	void UpdateMatricesBuffer();

	//Properties
	MyTexture* p_albedo = nullptr;
	MyTexture* p_normal = nullptr;
	XMFLOAT4 specularColor;
	FLOAT glossy;
	FLOAT specularPower;

	ConstantBuffer<PropertyData>* p_propertyBuffer = nullptr;

	XMFLOAT4X4* p_worldMatrix = nullptr;
	XMFLOAT4X4* p_viewMatrix = nullptr;
	XMFLOAT4X4* p_projectionMatrix = nullptr;

	ConstantBuffer<MatrixBuffer>* p_matrixBuffer = nullptr;
};

