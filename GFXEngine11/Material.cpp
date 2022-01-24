#include "Material.h"
#include "WICTextureLoader.h" // https://github.com/microsoft/DirectXTex/tree/main/WICTextureLoader
#include "Utils.h"
#include "WICTextureLoader.cpp"
#include <d3dcompiler.h>

INT Material::Init(ID3D11Device* _p_d3ddevice, LPCTSTR _texturename)
{
	INT error = CreateVertexShader(_p_d3ddevice);
	CheckError(error);

	error = CreatePixelShader(_p_d3ddevice);
	CheckError(error);

	/*HRESULT hr = CreateWICTextureFromFile(_p_d3ddevice, _texturename, &p_texture, 0 , WIC_LOADER_MIP_AUTOGEN);
	CheckFailed(hr, 60);*/

	//material.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Power = 1024.0f; // greater value, smaller the highlights
	////material.Emissive = { 1.0f, 0.0f, 0.0f, 1.0f };

	return 0;
}

void Material::Render(ID3D11DeviceContext* _p_d3ddevicecontext)
{
	//Set Sampler State
	//_p_d3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); //default: Wrap
	//_p_d3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//_p_d3ddevice->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0);
	//_p_d3ddevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//_p_d3ddevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC); //default: Point
	//_p_d3ddevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC); //default: Point
	//_p_d3ddevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16); //default: 1

	////Set Tex
	//_p_d3ddevice->SetTexture(0, p_texture);

	////Set Material
	//_p_d3ddevice->SetMaterial(&material);

	//Set Shader Pipeline
	_p_d3ddevicecontext->VSSetShader(p_VertexShader, nullptr, 0);
	_p_d3ddevicecontext->PSSetShader(p_PixelShader, nullptr, 0);
	_p_d3ddevicecontext->IASetInputLayout(p_InputLayout);
}

void Material::DeInit()
{
	//SafeRelease<IDirect3DTexture9>(p_texture);
	SafeRelease<ID3D11InputLayout>(p_InputLayout);
	SafeRelease<ID3D11PixelShader>(p_PixelShader);
	SafeRelease<ID3D11VertexShader>(p_VertexShader);
}

INT Material::CreateVertexShader(ID3D11Device* _p_d3ddevice)
{
	ID3DBlob* p_CompiledShaderCode = nullptr;

	// two Options to Load Shader
	//1. Compile Shader at Runtime (include d3dCompiler and load library)

	//HRESULT hr = D3DCompileFromFile(
	//	TEXT("ColorVertexShader.hlsl"), //hlsl Shader file
	//	nullptr, // Specify precomplier defines
	//	nullptr, // Additional Included Shader Code
	//	"main", //Main Fuction as entry point for shader
	//	"vs_4_0", //Coukd also be 5 dependent on GFX_Card // Shader type and Version
	//	0, // Additional Flags
	//	0,
	//	&p_CompiledShaderCode,
	//	nullptr // Optional Error Messages
	//);
	//CheckFailed(hr, 60);

	//2. Load already compiled Shader
	HRESULT hr = D3DReadFileToBlob(TEXT("ColorVertexShader.cso"), &p_CompiledShaderCode);
	CheckFailed(hr, 60);

	//Create Shader Code
	hr = _p_d3ddevice->CreateVertexShader(p_CompiledShaderCode->GetBufferPointer(), p_CompiledShaderCode->GetBufferSize(), nullptr, &p_VertexShader);
	CheckFailed(hr, 62);

	INT error = CreateInputLayout(_p_d3ddevice, p_CompiledShaderCode);
	CheckError(error);

	SafeRelease<ID3DBlob>(p_CompiledShaderCode);

	return 0;
}

INT Material::CreatePixelShader(ID3D11Device* _p_d3ddevice)
{
	ID3DBlob* p_CompiledShaderCode = nullptr;

	HRESULT hr = D3DReadFileToBlob(TEXT("ColorPixelShader.cso"), &p_CompiledShaderCode);
	CheckFailed(hr, 64);

	hr = _p_d3ddevice->CreatePixelShader(p_CompiledShaderCode->GetBufferPointer(), p_CompiledShaderCode->GetBufferSize(), nullptr, &p_PixelShader);
	CheckFailed(hr, 66);

	SafeRelease<ID3DBlob>(p_CompiledShaderCode);

	return 0;
}

INT Material::CreateInputLayout(ID3D11Device* _p_d3ddevice, ID3DBlob* _p_vertexshaderdata)
{
	//D3D11_INPUT_ELEMENT_DESC elements[] = 
	//{
	//	//Position 
	//	{
	//		"POSITION", // Semantic Name
	//		0, // semantic Index
	//		DXGI_FORMAT_R32G32B32A32_FLOAT, // Format
	//		0, // input Slot
	//		0, // aligned byte offset
	//		D3D11_INPUT_PER_VERTEX_DATA, // input slot Class
	//		0 // instance data step rate
	//	}
	//};

	D3D11_INPUT_ELEMENT_DESC elements[4] = {};

	//Position
	elements[0].SemanticName = "POSITION";
	elements[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//Position
	elements[1].SemanticName = "NORMAL";
	elements[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	//Position
	elements[2].SemanticName = "TEXTCOORD";
	elements[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elements[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	//Position
	elements[3].SemanticName = "COLOR";
	elements[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elements[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = _p_d3ddevice->CreateInputLayout(
		elements,
		4,
		_p_vertexshaderdata->GetBufferPointer(),
		_p_vertexshaderdata->GetBufferSize(),
		&p_InputLayout);


	CheckFailed(hr, 68);

	return 0;
}
