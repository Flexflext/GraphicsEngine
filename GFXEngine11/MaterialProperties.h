//Base Class for Material Properties
#pragma once
#include <d3d11.h>
#include "Utils.h"
#include <DirectXMath.h>
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "MyTexture.h"

using namespace DirectX;

class MaterialProperties
{
public:
	/// <summary>
	/// Initialize the Shader Properties => Full Virtual only Child Implementation can be Called
	/// </summary>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_worldmatrix"></param>
	/// <returns></returns>
	virtual INT InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice, XMFLOAT4X4* _worldmatrix) = 0;
	/// <summary>
	/// Update Properties => Full Virtual only Child Implementation can be Called
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// DeInititalize Properties => Full Virtual only Child Implementation can be Called
	/// </summary>
	virtual void DeinitProperties() = 0;

	//Type of Material
	EMaterials materialType;
protected:
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
	ID3D11Device* p_d3dDevice = nullptr;
};

