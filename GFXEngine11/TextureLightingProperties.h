#pragma once
#include "MaterialProperties.h"


class TextureLightingProperties : public MaterialProperties
{
public:
	TextureLightingProperties(LPCTSTR _texturename)
	{
		p_abledo = new MyTexture(_texturename, 0, true);
		materialType = EMaterials::TextureLighting;
	}

	INT InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice, XMFLOAT4X4* _worldmatrix) override;
	void DeinitProperties() override;
	void Update() override;

private:

	void SetMatrices(XMFLOAT4X4* _worldmatrix);
	void UpdateMatricesBuffer();

	MyTexture* p_abledo = nullptr;

	XMFLOAT4X4* p_worldMatrix = nullptr;
	XMFLOAT4X4* p_viewMatrix = nullptr;
	XMFLOAT4X4* p_projectionMatrix = nullptr;

	ConstantBuffer<MatrixBuffer>* p_matrixBuffer = nullptr;
};

