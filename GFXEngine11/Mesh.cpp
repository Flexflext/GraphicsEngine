#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"
#include <xutility>

using namespace DirectX;

INT Mesh::Init(ID3D11Device* _p_d3ddevice)
{
	INT error = InitVertexBuffer(_p_d3ddevice);
	CheckError(error);

	error = InitIndexBuffer(_p_d3ddevice);
	CheckError(error);

	//Initialize World Transformation-Matrix
	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity());

	return 0;
}

void Mesh::Update(FLOAT _dt)
{
	static FLOAT posX= 0.0f;
	static FLOAT posY= 0.0f;
	static FLOAT posZ= 0.0f;
	static FLOAT rotY = 0.0f;

	rotY += XM_PI / 3.0f * _dt;

	FLOAT move = 5.0f * _dt;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
	{
		posX -= move;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
	{
		posX += move;
	}

	if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
	{
		posY += move;
	}

	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
	{
		posY -= move;
	}

	if ((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) || (GetAsyncKeyState('Q') & 0x8000))
	{
		posZ -= move;
	}

	if ((GetAsyncKeyState(VK_ADD) & 0x8000) || (GetAsyncKeyState('E') & 0x8000))
	{
		posZ += move;
	}

	XMMATRIX translation = XMMatrixTranslation(posX, posY, posZ);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(0.0f, rotY, 0.0f);
	XMMATRIX localScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMStoreFloat4x4(&worldMatrix, localScale * rotation * translation);
}

void Mesh::Render(ID3D11DeviceContext* _p_d3ddevicecontext)
{
	

	//Set Mesh Data
	static UINT offset = 0;
	_p_d3ddevicecontext->IASetVertexBuffers(0, 1, &p_vertexBuffer, &vertexStride, &offset);
	_p_d3ddevicecontext->IASetIndexBuffer(p_indexBuffer, DXGI_FORMAT_R16_UINT, offset);
	_p_d3ddevicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Draw without Index Buffer
	//_p_D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6);
	//_p_D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, vertexCount - 2);
	//_p_D3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, vertexCount - 2);

	//Draw With Index Buffer
	_p_d3ddevicecontext->DrawIndexed(indexCount, 0, 0);
}

void Mesh::DeInit()
{
	SafeRelease<ID3D11Buffer>(p_vertexBuffer);
	SafeRelease<ID3D11Buffer>(p_indexBuffer);
}

INT Mesh::InitVertexBuffer(ID3D11Device* _p_d3ddevice)
{
	Vertex vertecies[] = {
		//// -->Quad with Triangle Fan<-- or with Index Buffer and triangle List and Color
		/*Vertex(-0.5f, 0.5f, 0.0f, 255u, 0u, 0u),
		Vertex(0.5f, 0.5f, 0.0f, 0u, 255u, 0u),
		Vertex(0.5f, -0.5f, 0.0f, 0u, 0u, 255u),
		Vertex(-0.5f, -0.5f, 0.0f, 255u, 0u, 255u),
		Vertex(0.0f, 0.0f, 0.0f, 255u, 255u, 255u),*/

		//// -->Quad with Triangle Fan<-- or with Index Buffer and triangle List with UV and Normal
		Vertex(-0.5f, 0.5f, 0.0f, 0.0f , 0.0f, -1.0f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
		Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
	};

	vertexCount = std::size(vertecies);
	vertexStride = sizeof(Vertex);

	D3D11_BUFFER_DESC desc = {};

	desc.ByteWidth = vertexCount * vertexStride;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE; // who has wich access

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = vertecies;

	HRESULT hr = _p_d3ddevice->CreateBuffer(&desc, &initialData, &p_vertexBuffer);
	CheckFailed(hr, 30);

	
	return 0;
}

INT Mesh::InitIndexBuffer(ID3D11Device* _p_d3ddevice)
{
	USHORT indices[] = {
		// -->Quad<-- 2 Tris
		//Primitive 1
		0,
		1,
		2,

		//Primitive 2
		0,
		2,
		3,
	};


	indexCount = std::size(indices);

	D3D11_BUFFER_DESC desc = {};

	desc.ByteWidth = indexCount * sizeof(USHORT);
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE; // who has wich access

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = indices;

	HRESULT hr = _p_d3ddevice->CreateBuffer(&desc, &initialData, &p_indexBuffer);
	CheckFailed(hr, 32);

	//// -->Quad<-- 4 Tris
	////Primitive 1
	//_pIndices[0] = 0;
	//_pIndices[1] = 1;
	//_pIndices[2] = 4;

	////Primitive 2
	//_pIndices[3] = 1;
	//_pIndices[4] = 2;
	//_pIndices[5] = 4;

	////Primitive 3
	//_pIndices[6] = 2;
	//_pIndices[7] = 3;
	//_pIndices[8] = 4;

	////Primitive 4
	//_pIndices[9] = 3;
	//_pIndices[10] = 0;
	//_pIndices[11] = 4;

	return 0;
}
