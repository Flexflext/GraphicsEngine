#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#define CheckError(error) if (error != 0) return error;
#define CheckNull(obj, error) if (obj == nullptr) return error;
#define CheckFailed(hr, error) if (FAILED(hr)) return error;

template<typename T>
void SafeRelease(T*& obj)
{
	if (obj != nullptr)
	{
		obj->Release();
		obj = nullptr;
	}
}

XMFLOAT3 Normalize(XMFLOAT3 _a)
{
	float l = sqrt(_a.x * _a.x + _a.y * _a.y + _a.z * _a.z);

	return XMFLOAT3(_a.x / l,  _a.y / l, _a.z / l);
}

XMFLOAT3 Subtract(XMFLOAT3 _a, XMFLOAT3 _b)
{
	return XMFLOAT3(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z);
}

XMFLOAT3 CrossProduct(XMFLOAT3 _a, XMFLOAT3 _b)
{
	return XMFLOAT3(_a.y * _b.z - _a.z * _b.y,
					_a.z * _b.x - _a.x * _b.z, 
					_a.x * _b.y - _a.y * _b.x);
}


#define D3DCOLORVALUE_RGB(r,g,b) { r / 255.0f, g/255.0f, b / 255.0f, 1.0f };
