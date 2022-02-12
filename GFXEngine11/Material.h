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
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext);
	void SetMaterialType() {};
	void Render();
	void DeInit();
	void SetMaterial(MaterialProperties* _props);
	void InitMatrices(XMFLOAT4X4* _p_worldmatrix);
private:

	
	INT CreateVertexShader(ID3D11Device* _p_d3ddevice);
	INT CreatePixelShader(ID3D11Device* _p_d3ddevice);
	INT CreateInputLayout(ID3D11Device* _p_d3ddevice, ID3DBlob* _p_vertexshaderdata);
	INT CreateMatrixBuffer(ID3D11Device* _p_d3ddevice);
	void SetMatrices(XMFLOAT4X4* _p_worldmatrix, XMFLOAT4X4* _p_viewmatrix, XMFLOAT4X4* _p_projectionmatrix);

	ID3D11VertexShader* p_vertexShader = nullptr;
	ID3D11PixelShader* p_pixelShader = nullptr;
	ID3D11InputLayout* p_inputLayout = nullptr;

	ID3D11Buffer* p_matrixBuffer = nullptr; // constant buffer for vertex shader

	struct MatrixBuffer 
	{
		XMFLOAT4X4 worldviewProjectionMatrix;
		XMFLOAT4X4 worldMatrix;
	};

	LPCTSTR vertexShaderName;
	LPCTSTR pixelShaderName;

	MaterialProperties* p_properties;

	//Optimizing
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
	XMFLOAT4X4* p_worldMatrix = nullptr;
	XMFLOAT4X4* p_viewMatrix = nullptr;
	XMFLOAT4X4* p_projectionMatrix = nullptr;
};

