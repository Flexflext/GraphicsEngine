#pragma once

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

enum class EComponentTypes
{
	C_Mesh,
	C_Light,
};




#define D3DCOLORVALUE_RGB(r,g,b) { r / 255.0f, g/255.0f, b / 255.0f, 1.0f };
