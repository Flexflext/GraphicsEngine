#pragma once
#include "MaterialProperties.h"
#include <DirectXMath.h>
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "MyTexture.h"
#include "MyCubemap.h"

using namespace DirectX;

class ReflectionShaderProperties : public MaterialProperties
{
public:
	ReflectionShaderProperties(LPCTSTR _texturename, LPCTSTR _normaltexturename, LPCTSTR _reflecttexturename, FLOAT _glossy, XMFLOAT4 _specularcolor, FLOAT _specularpower)
	{
		glossy = _glossy;
		specularPower = _specularpower;
		specularColor = _specularcolor;
		materialType = EMaterials::ReflectionShader;

		p_albedo = new MyTexture(_texturename, 0, true);
		p_normal = new MyTexture(_normaltexturename, 1, true);
		p_reflect = new MyCubemap(_reflecttexturename, 2, true);
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
	MyCubemap* p_reflect = nullptr;
	XMFLOAT4 specularColor;
	FLOAT glossy;
	FLOAT specularPower;

	ConstantBuffer<PropertyData>* p_propertyBuffer = nullptr;

	XMFLOAT4X4* p_worldMatrix = nullptr;
	XMFLOAT4X4* p_viewMatrix = nullptr;
	XMFLOAT4X4* p_projectionMatrix = nullptr;

	ConstantBuffer<MatrixBuffer>* p_matrixBuffer = nullptr;
};

