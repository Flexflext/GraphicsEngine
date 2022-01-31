#pragma once
#include <d3d11.h>
#include <DirectXMath.h>


#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

class Material
{
public:
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, LPCTSTR _texturename, XMFLOAT4X4* _p_worldmatrix, XMFLOAT4X4* _p_viewmatrix, XMFLOAT4X4* _p_projectionmatrix);
	void Render();
	void DeInit();

private:

	INT CreateVertexShader(ID3D11Device* _p_d3ddevice);
	INT CreatePixelShader(ID3D11Device* _p_d3ddevice);
	INT CreateInputLayout(ID3D11Device* _p_d3ddevice, ID3DBlob* _p_vertexshaderdata);
	INT CreateMatrixBuffer(ID3D11Device* _p_d3ddevice);
	void SetMatrices(ID3D11DeviceContext* _p_d3ddevicecontext, XMFLOAT4X4* _p_worldmatrix, XMFLOAT4X4* _p_viewmatrix, XMFLOAT4X4* _p_projectionmatrix);
	INT CreateTextureAndSampler(ID3D11Device* _p_d3ddevice, LPCTSTR _texturename);

	ID3D11VertexShader* p_vertexShader = nullptr;
	ID3D11PixelShader* p_pixelShader = nullptr;
	ID3D11InputLayout* p_inputLayout = nullptr;

	ID3D11Buffer* p_matrixBuffer = nullptr; // constant buffer for vertex shader

	struct MatrixBuffer 
	{
		XMFLOAT4X4 worldviewProjectionMatrix;
		XMFLOAT4X4 worldMatrix;
	};

	ID3D11ShaderResourceView* p_Texture = nullptr;
	ID3D11SamplerState* p_SamplerState = nullptr;

	//Optimizing
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
	XMFLOAT4X4* p_worldMatrix = nullptr;
	XMFLOAT4X4* p_viewMatrix = nullptr;
	XMFLOAT4X4* p_projectionMatrix = nullptr;
};
