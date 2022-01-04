#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"

INT Mesh::Init(IDirect3DDevice9* _p_D3DDevice)
{
	INT error = InitVertexBuffer(_p_D3DDevice);
	CheckError(error);

	error = InitIndexBuffer(_p_D3DDevice);
	CheckError(error);

	return 0;
}

void Mesh::Update(FLOAT _dt)
{
}

void Mesh::Render(IDirect3DDevice9* _p_D3DDevice)
{
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
	_pVertecies[0] = Vertex(-0.5f, 0.5f, 0.0f);
	_pVertecies[1] = Vertex(0.5f, 0.5f, 0.0f);
	_pVertecies[2] = Vertex(0.5f, -0.5f, 0.0f);
	_pVertecies[3] = Vertex(-0.5f, -0.5f, 0.0f);



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

	// -->Quad<--
	//Primitive 1
	_pIndices[0] = 0;
	_pIndices[1] = 1;
	_pIndices[2] = 2;

	//Primitive 2
	_pIndices[3] = 0;
	_pIndices[4] = 2;
	_pIndices[5] = 3;

	hr = p_vertexBuffer->Unlock();
	CheckFailed(hr, 39);

	_pIndices = nullptr;

	return 0;
}
