#pragma once
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")

class D3D
{
public:
	INT Init(HWND _hwnd, UINT _width, UINT _height, BOOL _fullscreen);
	void BeginScene(D3DCOLOR _backgroundcolor);
	void EndScene();
	void DeInit();

	IDirect3DDevice9* GetDevice() { return p_D3DDevice; }

private:
	IDirect3DDevice9* p_D3DDevice = nullptr; // Interface to D3D Pipeline (COM OBJ Component Object Model)
};

