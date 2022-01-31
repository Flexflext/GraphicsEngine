#include "Material.h"
#include "WICTextureLoader.h" // https://github.com/microsoft/DirectXTex/tree/main/WICTextureLoader
#include "Utils.h"
#include <d3dcompiler.h>

INT Material::Init(ID3D11Device* _p_d3ddevice, LPCTSTR _texturename)
{
	INT error = CreateVertexShader(_p_d3ddevice);
	CheckError(error);

	error = CreatePixelShader(_p_d3ddevice);
	CheckError(error);

	error = CreateMatrixBuffer(_p_d3ddevice);
	CheckError(error);

	error = CreateTextureAndSampler(_p_d3ddevice, _texturename);
	CheckError(error);

	return 0;
}

void Material::Render(ID3D11DeviceContext* _p_d3ddevicecontext, XMFLOAT4X4* _p_worldmatrix, XMFLOAT4X4* _p_viewmatrix, XMFLOAT4X4* _p_projectionmatrix)
{
	

	////Set Tex and Sampler State
	_p_d3ddevicecontext->PSSetShaderResources(0, 1, &p_Texture);
	_p_d3ddevicecontext->PSSetSamplers(0, 1, &p_SamplerState);

	////Set Material
	//_p_d3ddevice->SetMaterial(&material);

	//Set Shader Pipeline
	_p_d3ddevicecontext->VSSetShader(p_VertexShader, nullptr, 0);
	_p_d3ddevicecontext->PSSetShader(p_PixelShader, nullptr, 0);
	_p_d3ddevicecontext->IASetInputLayout(p_InputLayout);

	//Set Matrices
	SetMatrices(_p_d3ddevicecontext, _p_worldmatrix, _p_viewmatrix, _p_projectionmatrix);
}

void Material::DeInit()
{
	//SafeRelease<IDirect3DTexture9>(p_texture);
	SafeRelease<ID3D11ShaderResourceView>(p_Texture);
	SafeRelease<ID3D11SamplerState>(p_SamplerState);
	SafeRelease<ID3D11Buffer>(p_MatrixBuffer);
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
	//HRESULT hr = D3DReadFileToBlob(TEXT("ColorVertexShader.cso"), &p_CompiledShaderCode);
	//HRESULT hr = D3DReadFileToBlob(TEXT("TextureVertexShader.cso"), &p_CompiledShaderCode);
	HRESULT hr = D3DReadFileToBlob(TEXT("LightingVertexShader.cso"), &p_CompiledShaderCode);
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

	//HRESULT hr = D3DReadFileToBlob(TEXT("ColorPixelShader.cso"), &p_CompiledShaderCode);
	//HRESULT hr = D3DReadFileToBlob(TEXT("TexturePixelShader.cso"), &p_CompiledShaderCode);
	HRESULT hr = D3DReadFileToBlob(TEXT("LightingPixelShader.cso"), &p_CompiledShaderCode);
	CheckFailed(hr, 64);

	hr = _p_d3ddevice->CreatePixelShader(p_CompiledShaderCode->GetBufferPointer(), p_CompiledShaderCode->GetBufferSize(), nullptr, &p_PixelShader);
	CheckFailed(hr, 66);

	SafeRelease<ID3DBlob>(p_CompiledShaderCode);

	return 0;
}

INT Material::CreateInputLayout(ID3D11Device* _p_d3ddevice, ID3DBlob* _p_vertexshaderdata)
{
    //https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

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
	elements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	//Position
	elements[1].SemanticName = "NORMAL";
	elements[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	//Position
	elements[2].SemanticName = "TEXCOORD";
	elements[2].Format = DXGI_FORMAT_R32G32_FLOAT;
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

INT Material::CreateMatrixBuffer(ID3D11Device* _p_d3ddevice)
{
	D3D11_BUFFER_DESC desc = {};

	desc.ByteWidth = sizeof(MatrixBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = _p_d3ddevice->CreateBuffer(&desc, nullptr, &p_MatrixBuffer);
	CheckFailed(hr, 61);

	return 0;
}

void Material::SetMatrices(ID3D11DeviceContext* _p_d3ddevicecontext, XMFLOAT4X4* _p_worldmatrix, XMFLOAT4X4* _p_viewmatrix, XMFLOAT4X4* _p_projectionmatrix)
{
	XMMATRIX worldMatrix = XMLoadFloat4x4(_p_worldmatrix);
	XMMATRIX viewMatrix = XMLoadFloat4x4(_p_viewmatrix);
	XMMATRIX projectionMatrix = XMLoadFloat4x4(_p_projectionmatrix);

	XMMATRIX wvpMatrix = XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix); //transpose for column mayor - row mayor problem

	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = _p_d3ddevicecontext->Map(p_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr))
	{
		return;
	}

	MatrixBuffer* p_TempMatrixBuffer = static_cast<MatrixBuffer*>(data.pData);
	XMStoreFloat4x4(&(p_TempMatrixBuffer->worldviewProjectionMatrix), wvpMatrix);
	XMStoreFloat4x4(&(p_TempMatrixBuffer->worldMatrix), XMMatrixTranspose(worldMatrix));

	_p_d3ddevicecontext->Unmap(p_MatrixBuffer, 0);

	_p_d3ddevicecontext->VSSetConstantBuffers(0, 1, &p_MatrixBuffer);
}

INT Material::CreateTextureAndSampler(ID3D11Device* _p_d3ddevice, LPCTSTR _texturename)
{
	//Create Texture
	HRESULT hr = CreateWICTextureFromFile(_p_d3ddevice, _texturename, nullptr ,&p_Texture, 0);
	CheckFailed(hr, 63);


	//Create Sampler State
	D3D11_SAMPLER_DESC desc = {};

	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	hr = _p_d3ddevice->CreateSamplerState(&desc, &p_SamplerState);
	CheckFailed(hr, 65);

	return 0;
}
