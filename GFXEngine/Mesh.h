#pragma once
#include <d3d9.h>

class Mesh
{
public:
	INT Init(IDirect3DDevice9* _p_D3DDevice);
	void Update(FLOAT _dt);
	void Render(IDirect3DDevice9* _p_D3DDevice);
	void DeInit();
private:
	INT InitVertexBuffer(IDirect3DDevice9* _p_D3DDevice);
	INT InitIndexBuffer(IDirect3DDevice9* _p_D3DDevice);

	IDirect3DVertexBuffer9* p_vertexBuffer = nullptr;
	IDirect3DIndexBuffer9* p_indexBuffer = nullptr;

	INT vertexCount = 0; // Amount of Vertecies
	INT vertexStride = 0; // Size of one Vertex
	INT indexCount = 0; // Amount of Indecies


	D3DMATRIX worldMatrix = {};
};

