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
		position = _position;
		pixelShader = _shadertype;

		p_d3dDevice = _p_d3ddevice;
		p_d3dDeviceContext = _p_d3ddevicecontext;

		Init(_p_d3ddevice, _p_d3ddevicecontext);
		if (_initialdata != nullptr)
		{
			Update(_initialdata);
		}
	}

	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext);
	void Update(T* _data = nullptr);
	void DeInit();

private:
	T* p_bufferData = nullptr;
	ID3D11Buffer* p_constantBuffer = nullptr;

	ID3D11Device* p_d3dDevice = nullptr;
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;

	

	D3D11_MAPPED_SUBRESOURCE* p_subResource = nullptr;

	INT position = 0;
	bool pixelShader = false;
	HRESULT hr;
};


template<typename T>
inline INT ConstantBuffer<T>::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext)
{
	D3D11_BUFFER_DESC bufferDesc = {};

	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = _p_d3ddevice->CreateBuffer(&bufferDesc, nullptr, &p_constantBuffer);
	CheckFailed(hr, 62);



	return 0;
}

template<typename T>
inline void ConstantBuffer<T>::Update(T* _data)
{
	if (_data != nullptr)
	{

		D3D11_MAPPED_SUBRESOURCE* p_subResource = new D3D11_MAPPED_SUBRESOURCE();

		hr = p_d3dDeviceContext->Map(p_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, p_subResource);
		if (FAILED(hr))
		{
			return;
		}

		CopyMemory(p_subResource->pData, _data, sizeof(T));

		p_d3dDeviceContext->Unmap(p_constantBuffer, 0);
	}

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
	SafeRelease<ID3D11Buffer>(p_constantBuffer);
}