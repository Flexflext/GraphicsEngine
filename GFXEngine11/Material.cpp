#include "Material.h"
#include "WICTextureLoader.h" // https://github.com/microsoft/DirectXTex/tree/main/WICTextureLoader
#include "Utils.h"
#include <d3dcompiler.h>
#include "Camera.h"
#include "AllCameras.h"
#include "TextureLightingProperties.h"

INT Material::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;

	INT error = CreateVertexShader(_p_d3ddevice);
	CheckIntError(error);

	error = CreatePixelShader(_p_d3ddevice);
	CheckIntError(error);

	error = CreateMatrixBuffer(_p_d3ddevice);
	CheckIntError(error);

	error = p_properties->InitProperties(_p_d3ddevicecontext, _p_d3ddevice);
	CheckIntError(error);

	return 0;
}

void Material::Render()
{
	p_properties->Update();

	//Set Shader Pipeline
	p_d3dDeviceContext->VSSetShader(p_vertexShader, nullptr, 0);
	p_d3dDeviceContext->PSSetShader(p_pixelShader, nullptr, 0);
	p_d3dDeviceContext->IASetInputLayout(p_inputLayout);

	//Set Matrices
	SetMatrices(p_worldMatrix, p_viewMatrix, p_projectionMatrix);
}

void Material::DeInit()
{
	SafeRelease<ID3D11Buffer>(p_matrixBuffer);
	SafeRelease<ID3D11InputLayout>(p_inputLayout);
	SafeRelease<ID3D11PixelShader>(p_pixelShader);
	SafeRelease<ID3D11VertexShader>(p_vertexShader);
	SafeRelease<ID3D11DeviceContext>(p_d3dDeviceContext);

	p_properties->DeinitProperties();
}

void Material::SetMaterial(MaterialProperties* _props)
{
	p_properties = _props;

	switch (p_properties->materialType)
	{
	case EMaterials::TextureLighting:
	{
		vertexShaderName = TEXT("LightingVertexShader.cso");
		pixelShaderName = TEXT("LightingPixelShader.cso");
		break;
	}
	case EMaterials::SpecularLight:
	{
		vertexShaderName = TEXT("SpecularVertexShader.cso");
		pixelShaderName = TEXT("SpecularPixelShader.cso");
		break;
	}
	}
}

void Material::InitMatrices(XMFLOAT4X4* _p_worldmatrix)
{
	Camera* cam = AllCameras::GetMainCamera();

	p_worldMatrix = _p_worldmatrix;
	p_viewMatrix = cam->GetViewMatrix();
	p_projectionMatrix = cam->GetProjectionMatrix();
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
	HRESULT hr = D3DReadFileToBlob(vertexShaderName, &p_CompiledShaderCode);
	CheckFailed(hr, 60);

	//Create Shader Code
	hr = _p_d3ddevice->CreateVertexShader(p_CompiledShaderCode->GetBufferPointer(), p_CompiledShaderCode->GetBufferSize(), nullptr, &p_vertexShader);
	CheckFailed(hr, 62);

	INT error = CreateInputLayout(_p_d3ddevice, p_CompiledShaderCode);
	CheckIntError(error);

	SafeRelease<ID3DBlob>(p_CompiledShaderCode);

	return 0;
}

INT Material::CreatePixelShader(ID3D11Device* _p_d3ddevice)
{
	ID3DBlob* p_CompiledShaderCode = nullptr;

	//HRESULT hr = D3DReadFileToBlob(TEXT("ColorPixelShader.cso"), &p_CompiledShaderCode);
	//HRESULT hr = D3DReadFileToBlob(TEXT("TexturePixelShader.cso"), &p_CompiledShaderCode);
	HRESULT hr = D3DReadFileToBlob(pixelShaderName, &p_CompiledShaderCode);
	CheckFailed(hr, 64);

	hr = _p_d3ddevice->CreatePixelShader(p_CompiledShaderCode->GetBufferPointer(), p_CompiledShaderCode->GetBufferSize(), nullptr, &p_pixelShader);
	CheckFailed(hr, 66);

	SafeRelease<ID3DBlob>(p_CompiledShaderCode);

	return 0;
}

INT Material::CreateInputLayout(ID3D11Device* _p_d3ddevice, ID3DBlob* _p_vertexshaderdata)
{
    //https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics
	D3D11_INPUT_ELEMENT_DESC elements[6] = {};

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

	////Tangent
	//elements[4].SemanticName = "TANGENT";
	//elements[4].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//elements[4].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	////Binormal
	//elements[5].SemanticName = "BINORMAL";
	//elements[5].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//elements[5].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = _p_d3ddevice->CreateInputLayout(
		elements,
		4,
		_p_vertexshaderdata->GetBufferPointer(),
		_p_vertexshaderdata->GetBufferSize(),
		&p_inputLayout);


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

	HRESULT hr = _p_d3ddevice->CreateBuffer(&desc, nullptr, &p_matrixBuffer);
	CheckFailed(hr, 61);

	

	return 0;
}

void Material::SetMatrices(XMFLOAT4X4* _p_worldmatrix, XMFLOAT4X4* _p_viewmatrix, XMFLOAT4X4* _p_projectionmatrix)
{
	XMMATRIX worldMatrix = XMLoadFloat4x4(_p_worldmatrix);
	XMMATRIX viewMatrix = XMLoadFloat4x4(_p_viewmatrix);
	XMMATRIX projectionMatrix = XMLoadFloat4x4(_p_projectionmatrix);

	XMMATRIX wvpMatrix = XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix); //transpose for column mayor - row mayor problem

	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = p_d3dDeviceContext->Map(p_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr))
	{
		return;
	}

	MatrixBuffer* p_TempMatrixBuffer = static_cast<MatrixBuffer*>(data.pData);
	XMStoreFloat4x4(&(p_TempMatrixBuffer->worldviewProjectionMatrix), wvpMatrix);
	XMStoreFloat4x4(&(p_TempMatrixBuffer->worldMatrix), XMMatrixTranspose(worldMatrix));
	p_TempMatrixBuffer->camWorldPos = AllCameras::GetMainCamera()->gameObject->transform.Position;

	p_d3dDeviceContext->Unmap(p_matrixBuffer, 0);

	p_d3dDeviceContext->VSSetConstantBuffers(0, 1, &p_matrixBuffer);
}
