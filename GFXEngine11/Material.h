#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Utils.h"
#include "MaterialProperties.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

class Material
{
public:
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, XMFLOAT4X4* _p_worldmatrix);
	void SetMaterialType() {};
	void Render();
	void DeInit();
	void SetMaterial(MaterialProperties* _props);
private:

	
	INT CreateVertexShader(ID3D11Device* _p_d3ddevice);
	INT CreatePixelShader(ID3D11Device* _p_d3ddevice);
	INT CreateInputLayout(ID3D11Device* _p_d3ddevice, ID3DBlob* _p_vertexshaderdata);

	ID3D11VertexShader* p_vertexShader = nullptr;
	ID3D11PixelShader* p_pixelShader = nullptr;
	ID3D11InputLayout* p_inputLayout = nullptr;

	LPCTSTR vertexShaderName;
	LPCTSTR pixelShaderName;

	MaterialProperties* p_properties;

	//Optimizing
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
};

