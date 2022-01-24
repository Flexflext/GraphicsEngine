#pragma once
#include <d3d11.h>

#pragma comment(lib, "d3dcompiler.lib")

class Material
{
public:
	INT Init(ID3D11Device* _p_d3ddevice, LPCTSTR _texturename);
	void Render(ID3D11DeviceContext* _p_d3ddevicecontext);
	void DeInit();

private:

	INT CreateVertexShader(ID3D11Device* _p_d3ddevice);
	INT CreatePixelShader(ID3D11Device* _p_d3ddevice);

	INT CreateInputLayout(ID3D11Device* _p_d3ddevice, ID3DBlob* _p_vertexshaderdata);

	ID3D11VertexShader* p_VertexShader = nullptr;
	ID3D11PixelShader* p_PixelShader = nullptr;
	ID3D11InputLayout* p_InputLayout = nullptr;

	/*IDirect3DTexture9* p_texture;
	D3DMATERIAL9 material = {};*/
};

