#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"
#include <DirectXMath.h>

using namespace DirectX;

INT Mesh::Init(IDirect3DDevice9* _p_D3DDevice)
{
	INT error = InitVertexBuffer(_p_D3DDevice);
	CheckIntError(error);

	error = InitIndexBuffer(_p_D3DDevice);
	CheckIntError(error);

	//Initialize World Transformation-Matrix
	XMMATRIX identity = XMMatrixIdentity();
	XMFLOAT4X4 world = {};
	XMStoreFloat4x4(&world, identity);

	worldMatrix = *reinterpret_cast<D3DMATRIX*>(&world);


	return 0;
}

void Mesh::Update(FLOAT _dt)
{
	static FLOAT posX= 0.0f;
	static FLOAT posY= 0.0f;
	static FLOAT posZ= 0.0f;
	static FLOAT rotZ = 0.0f;

	rotZ += XM_PI / 3.0f * _dt;

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
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	XMMATRIX localScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&worldMatrix), localScale * rotation * translation);
}

void Mesh::Render(IDirect3DDevice9* _p_D3DDevice)
{
	//Set World Transformmation-Matrix
	_p_D3DDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

	// Set Flexible Vertex Format
	_p_D3DDevice->SetFVF(FVF);

	//Set Vertex Buffer Source
	_p_D3DDevice->SetStreamSource(0, p_vertexBuffer, 0, vertexStride);

	//Draw without Index Buffer
	//_p_D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6);
	//_p_D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, vertexCount - 2);
	//_p_D3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, vertexCount - 2);

	//Draw With Index Buffer
	_p_D3DDevice->SetIndices(p_indexBuffer);
	_p_D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, indexCount / 3);
}

void Mesh::DeInit()
{
	SafeRelease<IDirect3DVertexBuffer9>(p_vertexBuffer);
	SafeRelease<IDirect3DIndexBuffer9>(p_indexBuffer);
}

INT Mesh::InitVertexBuffer(IDirect3DDevice9* _p_D3DDevice)
{
	vertexCount = 4;
	vertexStride = sizeof(Vertex);

	HRESULT hr = _p_D3DDevice->CreateVertexBuffer(
		vertexCount * vertexStride, //byte length of buffer
		D3DUSAGE_WRITEONLY, // give write Acces
		FVF, // Flexible Vertex Format
		D3DPOOL_MANAGED, //Managed Memory manegement
		&p_vertexBuffer,
		nullptr);

	CheckFailed(hr, 30);

	Vertex* _pVertecies = nullptr;
	hr = p_vertexBuffer->Lock(0, 0, reinterpret_cast<void**>(&_pVertecies), 0);
	CheckFailed(hr, 32);


	// -->Triangle<--
	/*_pVertecies[0] = Vertex(0.0f, 0.5f, 0.0f);
	_pVertecies[1] = Vertex(0.5f, -0.5f, 0.0f);
	_pVertecies[2] = Vertex(-0.5f, -0.5f, 0.0f);*/

	// -->Quad Withoud index Buffer and Triangle List<--
	//Primitve 1
	/*_pVertecies[0] = Vertex(-0.5f, 0.5f, 0.0f);
	_pVertecies[1] = Vertex(0.5f, 0.5f, 0.0f);
	_pVertecies[2] = Vertex(0.5f, -0.5f, 0.0f);*/

	//Primitve 2
	/*_pVertecies[3] = Vertex(-0.5f, 0.5f, 0.0f);
	_pVertecies[4] = Vertex(0.5f, -0.5f, 0.0f);
	_pVertecies[5] = Vertex(-0.5f, -0.5f, 0.0f);*/

	// -->Quad with Triangle Strip<--
	/*_pVertecies[0] = Vertex(-0.5f, 0.5f, 0.0f);
	_pVertecies[1] = Vertex(0.5f, 0.5f, 0.0f);
	_pVertecies[2] = Vertex(-0.5f, -0.5f, 0.0f);
	_pVertecies[3] = Vertex(0.5f, -0.5f, 0.0f);*/

	// -->Quad with Triangle Fan<-- or with Index Buffer and triangle List
	/*_pVertecies[0] = Vertex(-0.5f, 0.5f, 0.0f);
	_pVertecies[1] = Vertex(0.5f, 0.5f, 0.0f);
	_pVertecies[2] = Vertex(0.5f, -0.5f, 0.0f);
	_pVertecies[3] = Vertex(-0.5f, -0.5f, 0.0f);*/

	// -->Quad with Triangle Fan<-- or with Index Buffer and triangle List and Color
	/*_pVertecies[0] = Vertex(-0.5f, 0.5f, 0.0f, 255, 0, 0);
	_pVertecies[1] = Vertex(0.5f, 0.5f, 0.0f, 0, 255, 0);
	_pVertecies[2] = Vertex(0.5f, -0.5f, 0.0f, 0, 0, 255);
	_pVertecies[3] = Vertex(-0.5f, -0.5f, 0.0f, 255, 0, 255);
	_pVertecies[4] = Vertex(0.0f, 0.0f, 0.0f, 255, 255, 255);*/

	// -->Quad with Triangle Fan<-- or with Index Buffer and triangle List with UV
	/*_pVertecies[0] = Vertex(-0.5f, 0.5f, 0.0f, -1.0f, -1.0f);
	_pVertecies[1] = Vertex(0.5f, 0.5f, 0.0f, 2.0f, -1.0f);
	_pVertecies[2] = Vertex(0.5f, -0.5f, 0.0f, 2.0f, 2.0f);
	_pVertecies[3] = Vertex(-0.5f, -0.5f, 0.0f, -1.0f, 2.0f);*/

	// -->Quad with Triangle Fan<-- or with Index Buffer and triangle List with UV and Normal
	_pVertecies[0] = Vertex(-0.5f, 0.5f, 0.0f, 0.0f , 0.0f, -1.0f, 0.0f, 0.0f);
	_pVertecies[1] = Vertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	_pVertecies[2] = Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	_pVertecies[3] = Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);



	hr = p_vertexBuffer->Unlock();
	CheckFailed(hr, 34);

	_pVertecies = nullptr;

	return 0;
}

INT Mesh::InitIndexBuffer(IDirect3DDevice9* _p_D3DDevice)
{
	indexCount = 6;

	HRESULT hr = _p_D3DDevice->CreateIndexBuffer(indexCount * sizeof(USHORT), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &p_indexBuffer, nullptr);
	CheckFailed(hr, 36);

	USHORT* _pIndices = nullptr;
	hr = p_indexBuffer->Lock(0, 0, reinterpret_cast<void**>(&_pIndices), 0);
	CheckFailed(hr, 38);

	// -->Quad<-- 2 Tris
	//Primitive 1
	_pIndices[0] = 0;
	_pIndices[1] = 1;
	_pIndices[2] = 2;

	//Primitive 2
	_pIndices[3] = 0;
	_pIndices[4] = 2;
	_pIndices[5] = 3;

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

	hr = p_vertexBuffer->Unlock();
	CheckFailed(hr, 39);

	_pIndices = nullptr;

	return 0;
}
