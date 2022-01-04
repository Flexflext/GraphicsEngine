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
