#pragma once

#define CheckIntError(error) if (error != 0) return error;
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
	C_Camera,
	CS_FreeLookCam
};

enum class EMaterials
{
	TextureLighting,
	SpecularLight,
	NormalShader,
};

unsigned int WindowWidth = 1024;
unsigned int WindowHeight = 768;
int isFullScreen = false;


#define D3DCOLORVALUE_RGB(r,g,b) { r / 255.0f, g/255.0f, b / 255.0f, 1.0f };
