#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Mesh
{
public:
	INT Init(ID3D11Device* _p_d3ddevice);
	void Update(FLOAT _dt);
	void Render(ID3D11DeviceContext* _p_d3ddevicecontext);
	void DeInit();
private:
	INT InitVertexBuffer(ID3D11Device* _p_D3DDevice);
	INT InitIndexBuffer(ID3D11Device* _p_D3DDevice);

	ID3D11Buffer* p_vertexBuffer = nullptr;
	ID3D11Buffer* p_indexBuffer = nullptr;

	UINT vertexCount = 0; // Amount of Vertecies
	UINT vertexStride = 0; // Size of one Vertex
	UINT indexCount = 0; // Amount of Indecies


	XMFLOAT4X4 worldMatrix = {};
};

