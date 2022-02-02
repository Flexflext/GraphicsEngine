#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Vertex.h"
#include "Component.h"

using namespace DirectX;

class Mesh //: public Component
{
public:
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt);
	void Update();
	void Render();
	void DeInit();

	XMFLOAT4X4* GetWorldMatrix() { return &worldMatrix; }

private:
	INT InitVertexBuffer(ID3D11Device* _p_D3DDevice);
	INT InitIndexBuffer(ID3D11Device* _p_D3DDevice);

	INT RecalculateNormals(ID3D11Device* _p_d3ddevice);
	

	ID3D11Buffer* p_vertexBuffer = nullptr;
	ID3D11Buffer* p_indexBuffer = nullptr;

	UINT vertexCount = 0; // Amount of Vertecies
	UINT vertexStride = 0; // Size of one Vertex
	UINT indexCount = 0; // Amount of Indecies

	Vertex* vertexData = nullptr;
	USHORT* indexData = nullptr;

	XMFLOAT4X4 worldMatrix = {};

	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
	FLOAT* p_deltaTime = nullptr;
};

