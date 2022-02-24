//Matrial Class to Set Shaders and Shader Properties
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
	/// <summary>
	/// Initialize the Material and Create the Shaders
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <param name="_p_worldmatrix"></param>
	/// <returns></returns>
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, XMFLOAT4X4* _p_worldmatrix);
	/// <summary>
	/// Render and Update the Material Type and Give the Properties to the Shader
	/// </summary>
	void Render();
	/// <summary>
	/// DeInitialize the Material and the Material Properties
	/// </summary>
	void DeInit();
	/// <summary>
	/// Set the Materialproperties of the Material
	/// </summary>
	/// <param name="_props"></param>
	void SetMaterial(MaterialProperties* _props);
private:

	/// <summary>
	/// Create a Vertex Shader
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <returns></returns>
	INT CreateVertexShader(ID3D11Device* _p_d3ddevice);
	/// <summary>
	/// Create the PixelShader
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <returns></returns>
	INT CreatePixelShader(ID3D11Device* _p_d3ddevice);
	/// <summary>
	/// Create the Input Layout for the Vertex Shader
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_vertexshaderdata"></param>
	/// <returns></returns>
	INT CreateInputLayout(ID3D11Device* _p_d3ddevice, ID3DBlob* _p_vertexshaderdata);

	ID3D11VertexShader* p_vertexShader = nullptr;
	ID3D11PixelShader* p_pixelShader = nullptr;
	ID3D11InputLayout* p_inputLayout = nullptr;

	LPCTSTR vertexShaderName;
	LPCTSTR pixelShaderName;

	//Material Properties 
	MaterialProperties* p_properties = nullptr;

	//Optimizing
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
};

