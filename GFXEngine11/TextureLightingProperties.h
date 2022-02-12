#pragma once
#include "MaterialProperties.h"

class TextureLightingProperties : public MaterialProperties
{
public:
	TextureLightingProperties(LPCTSTR _texturename)
	{
		textureName = _texturename;
		materialType = EMaterials::TextureLighting;
	}

	INT InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice) override;
	void DeinitProperties() override;
	void Update() override;

private:
	//PropertiesAddOns
	ID3D11ShaderResourceView* p_texture = nullptr;
	ID3D11SamplerState* p_samplerState = nullptr;

	//Properties
	LPCTSTR textureName;
	
};

