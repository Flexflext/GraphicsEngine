#pragma once
#include "MaterialProperties.h"
#include <DirectXMath.h>

using namespace DirectX;

class SpecularLightingProperties : public MaterialProperties
{
public:
	SpecularLightingProperties(LPCTSTR _texturename, FLOAT _glossy, XMFLOAT4 _specularcolor, FLOAT _specularpower)
	{
		textureName = _texturename;
		glossy = _glossy;
		specularPower = _specularpower;
		specularColor = _specularcolor;
		materialType = EMaterials::SpecularLight;
	}

	struct PropertyData
	{
		// because of 16 byte alignment
		XMFLOAT4 specularColor;
		FLOAT glossy;
		FLOAT specularPower;
		XMFLOAT2 padding;
	};

	INT InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice) override;
	void DeinitProperties() override;
	void Update() override;

private:
	//PropertiesAddOns
	ID3D11ShaderResourceView* p_texture = nullptr;
	ID3D11ShaderResourceView* p_sectexture = nullptr;
	ID3D11SamplerState* p_samplerState = nullptr;

	//Properties
	LPCTSTR textureName;
	XMFLOAT4 specularColor;
	FLOAT glossy;
	FLOAT specularPower;

	PropertyData* p_propData = nullptr;

	ID3D11Buffer* p_propBuffer = nullptr;
};

