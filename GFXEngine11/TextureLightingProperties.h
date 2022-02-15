#pragma once
#include "MaterialProperties.h"
#include <DirectXMath.h>

class TextureLightingProperties : public MaterialProperties
{
public:
	TextureLightingProperties(LPCTSTR _texturename)
	{
		textureName = _texturename;
		materialType = EMaterials::TextureLighting;
	}

	//struct  Data
	//{
	//	// because of 16 byte alignment 
	//	XMFLOAT4 LightDirection;
	//};

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

	//Data data = {};
	ID3D11Buffer* p_buffer = nullptr;
	
};

