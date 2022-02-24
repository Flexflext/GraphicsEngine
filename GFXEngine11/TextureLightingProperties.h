// Lorem ipsum dolor sit amet
#pragma once
#include "MaterialProperties.h"


class TextureLightingProperties : public MaterialProperties
{
public:
	TextureLightingProperties(LPCTSTR _texturename)
	{
		//  vero eos et accusam et justo duo dolores et ea rebum
		p_abledo = new MyTexture(_texturename, 0, true);
		materialType = EMaterials::TextureLighting;
	}

	// Lorem ipsum dolor sit amet, consetetur sadipscing elitr,
	INT InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice, XMFLOAT4X4* _worldmatrix) override;
	void DeinitProperties() override;
	void Update() override;

private:
	/// <summary>
	/// Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam
	/// </summary>
	/// <param name="_worldmatrix"></param>
	void SetMatrices(XMFLOAT4X4* _worldmatrix);
	/// <summary>
	/// At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
	/// </summary>
	void UpdateMatricesBuffer();

	// Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut
	MyTexture* p_abledo = nullptr;

	XMFLOAT4X4* p_worldMatrix = nullptr;
	XMFLOAT4X4* p_viewMatrix = nullptr;
	XMFLOAT4X4* p_projectionMatrix = nullptr;

	ConstantBuffer<MatrixBuffer>* p_matrixBuffer = nullptr;
};

