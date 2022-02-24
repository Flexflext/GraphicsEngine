//Extra Utilities
#pragma once
//Extra Defines
#define CheckIntError(error) if (error != 0) return error;
#define CheckNull(obj, error) if (obj == nullptr) return error;
#define CheckFailed(hr, error) if (FAILED(hr)) return error;

/// <summary>
/// Safe-Release for Com Objects
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="obj"></param>
template<typename T>
void SafeRelease(T*& obj)
{
	if (obj != nullptr)
	{
		obj->Release();
		obj = nullptr;
	}
}

//Material Shader Types
enum class EMaterials
{
	TextureLighting,
	SpecularLight,
	NormalShader,
	ReflectionShader,
};

//Window Shit
unsigned int WindowWidth = 1024;
unsigned int WindowHeight = 768;
int isFullScreen = false;

//Define for ColorValue float 0-1 to 0-255
#define D3DCOLORVALUE_RGB(r,g,b) { r / 255.0f, g/255.0f, b / 255.0f, 1.0f };
