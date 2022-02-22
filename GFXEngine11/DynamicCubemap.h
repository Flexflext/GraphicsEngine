#pragma once
#include <d3d11.h>

class DynamicCubemap
{
public:
	void BuildDynamicCubeMap();
	ID3D11RenderTargetView* p_renderTargetView = nullptr;
	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;
};

