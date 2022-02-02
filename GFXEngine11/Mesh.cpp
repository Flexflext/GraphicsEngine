#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"
#include <xutility>

using namespace DirectX;

INT Mesh::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;
	p_deltaTime = _p_dt;

	INT error = InitVertexBuffer(_p_d3ddevice);
	CheckError(error);

	error = InitIndexBuffer(_p_d3ddevice);
	CheckError(error);

	/*error = RecalculateNormals(_p_d3ddevice);
	CheckError(error);*/

	//Initialize World Transformation-Matrix
	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity());

	return 0;
}

void Mesh::Update()
{
	static FLOAT posX= 0.0f;
	static FLOAT posY= 0.0f;
	static FLOAT posZ= 0.0f;
	static FLOAT rotY = 0.0f;

	rotY += XM_PI / 3.0f * *p_deltaTime;

	FLOAT move = 5.0f * *p_deltaTime;

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
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(rotY * 0.5f, rotY, 0.0f);
	XMMATRIX localScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMStoreFloat4x4(&worldMatrix, localScale * rotation * translation);
}

void Mesh::Render()
{
	

	//Set Mesh Data
	static UINT offset = 0;
	p_d3dDeviceContext->IASetVertexBuffers(0, 1, &p_vertexBuffer, &vertexStride, &offset);
	p_d3dDeviceContext->IASetIndexBuffer(p_indexBuffer, DXGI_FORMAT_R16_UINT, offset);
	p_d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Draw without Index Buffer
	//_p_D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6);
	//_p_D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, vertexCount - 2);
	//_p_D3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, vertexCount - 2);

	//Draw With Index Buffer
	p_d3dDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void Mesh::DeInit()
{
	SafeRelease<ID3D11Buffer>(p_vertexBuffer);
	SafeRelease<ID3D11Buffer>(p_indexBuffer);
	SafeRelease<ID3D11DeviceContext>(p_d3dDeviceContext);
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
		//Front
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f , 0.0f, -1.0f, 0.0f, 0.0f), // 0
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f), // 1
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f), // 2
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f), // 3

		//Back
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f), // 4
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f), // 5
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f), // 6
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f), // 7

		//Top
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f), // 1 // 8
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f), // 5 // 9
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f), // 6 // 10
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f), // 2 // 11

		//Bottom
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f), // 4 // 12
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f , -1.0f, 0.0f, 0.0f, 1.0f), // 0 // 13
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f), // 3 // 14
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f), // 7 // 15

		//Left
		Vertex(-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f), // 4 // 16
		Vertex(-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f), // 5 // 17
		Vertex(-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f), // 1 // 18
		Vertex(-0.5f, -0.5f, -0.5f, -1.0f , 0.0f, 0.0f, 1.0f, 0.0f), // 0 // 19

		//Right
		Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f), // 3 // 20
		Vertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f), // 2 // 21
		Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f), // 6 // 22
		Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f), // 7 // 23
	};
	Vertex vert[std::size(vertecies)];
	vertexCount = std::size(vertecies);
	vertexStride = sizeof(Vertex);

	//vertexData = static_cast<Vertex*>(malloc(vertexStride * vertexCount));
	std::copy(std::begin(vertecies), std::end(vertecies), std::begin(vert));
	vertexData = vert;

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
		// -->Cube<--
		//Front
		0,1,2,
		0,2,3,
		//back
		4,6,5,
		4,7,6,
		//left
		16,17,18,
		16,18,19,
		//right
		20,21,22,
		20,22,23,
		//top
		8,9,10,
		8,10,11,
		//bottom
		12,13,14,
		12,14,15
	};


	indexCount = std::size(indices);

	USHORT index[std::size(indices)];

	//indexData = static_cast<USHORT*>(malloc(sizeof(USHORT) * indexCount));

	std::copy(std::begin(indices), std::end(indices), std::begin(index));

	indexData = index;

	D3D11_BUFFER_DESC desc = {};

	desc.ByteWidth = indexCount * sizeof(USHORT);
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE; // who has wich access

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = indices;

	HRESULT hr = _p_d3ddevice->CreateBuffer(&desc, &initialData, &p_indexBuffer);
	CheckFailed(hr, 32);

	return 0;
}

INT Mesh::RecalculateNormals(ID3D11Device* _p_d3ddevice)
{
	for (int i = 0; i < indexCount; i += 3)
	{
		USHORT indexA = indexData[i];
		USHORT indexB = indexData[i + 1];
		USHORT indexC = indexData[i + 2];

		Vertex curVertexPos = vertexData[indexA];
		Vertex curVertexPos1 = vertexData[indexB];
		Vertex curVertexPos2 = vertexData[indexC];

		XMVECTOR posA = XMVectorSet(curVertexPos.position.x, curVertexPos.position.y, curVertexPos.position.z, 0.0f);
		XMVECTOR posB = XMVectorSet(curVertexPos1.position.x, curVertexPos1.position.y, curVertexPos1.position.z, 0.0f);
		XMVECTOR posC = XMVectorSet(curVertexPos2.position.x, curVertexPos2.position.y, curVertexPos2.position.z, 0.0f);

		XMVECTOR Normalized = XMVector3Normalize((posB - posC) * (posC - posA));

		XMFLOAT3 Normal;
		Normal.x = XMVectorGetX(Normalized);
		Normal.y = XMVectorGetY(Normalized);
		Normal.z = XMVectorGetZ(Normalized);

		curVertexPos.normal = Normal;
		curVertexPos1.normal = Normal;
		curVertexPos2.normal = Normal;
	}

	D3D11_BUFFER_DESC desc = {};

	desc.ByteWidth = vertexCount * vertexStride;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE; // who has wich access

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = vertexData;

	HRESULT hr = _p_d3ddevice->CreateBuffer(&desc, &initialData, &p_vertexBuffer);
	CheckFailed(hr, 31);

	return 0;
}
