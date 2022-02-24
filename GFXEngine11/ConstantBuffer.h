//Generic Constant Buffer 
#pragma once
#include <d3d11.h>
#include "Utils.h"
#include <DirectXMath.h>
#include "ConstantBufferTypes.h"

using namespace DirectX;


template<typename T>
class ConstantBuffer
{
public:
	ConstantBuffer(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, INT _position, bool _shadertype, T* _initialdata = nullptr)
	{
		//Set Position and Shader Type
		position = _position;
		pixelShader = _shadertype;

		//Set Device and Context
		p_d3dDevice = _p_d3ddevice;
		p_d3dDeviceContext = _p_d3ddevicecontext;

		//Initialize the Constant Buffer
		Init(_p_d3ddevice, _p_d3ddevicecontext);
		//Update Initilally to not have to Update all the Time
		if (_initialdata != nullptr)
		{
			Update(_initialdata);
		}
	}

	/// <summary>
	/// Initialize the Constant Buffer
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <returns></returns>
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext);
	/// <summary>
	/// Update the Constant Buffer with new Data
	/// </summary>
	/// <param name="_data"></param>
	void Update(T* _data = nullptr);
	/// <summary>
	/// Deinitialize the Constant Buffer
	/// </summary>
	void DeInit();

private:
	ID3D11Buffer* p_constantBuffer = nullptr;

	ID3D11Device* p_d3dDevice = nullptr;
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;

	INT position = 0;
	bool pixelShader = false;
	HRESULT hr;
};


template<typename T>
inline INT ConstantBuffer<T>::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext)
{
	//Set Buffer Description
	D3D11_BUFFER_DESC bufferDesc = {};

	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16))); //Is Dividable by 16
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // is Constant Buffer
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC; // Can be Rewritten
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 

	//Create the Buffer
	hr = _p_d3ddevice->CreateBuffer(&bufferDesc, nullptr, &p_constantBuffer);
	CheckFailed(hr, 62);

	return 0;
}

template<typename T>
void ConstantBuffer<T>::Update(T* _data)
{
	if (_data != nullptr)
	{
		//Create Subresource
		D3D11_MAPPED_SUBRESOURCE subResource = {};

		//Map the Data
		hr = p_d3dDeviceContext->Map(p_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		if (FAILED(hr))
		{
			return;
		}

		//Copy the Data Memory to the Subresource Data
		CopyMemory(subResource.pData, _data, sizeof(T));

		//Unmap the Constantbuffer
		p_d3dDeviceContext->Unmap(p_constantBuffer, 0);
	}

	//Set Constant Buffer or PixelShader
	if (pixelShader)
	{
		p_d3dDeviceContext->PSSetConstantBuffers(position, 1, &p_constantBuffer);
	}
	else
	{
		p_d3dDeviceContext->VSSetConstantBuffers(position, 1, &p_constantBuffer);
	}
}

template<typename T>
inline void ConstantBuffer<T>::DeInit()
{
	//Release the ConstantBuffer
	SafeRelease<ID3D11Buffer>(p_constantBuffer);
}