#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Vertex.h"
#include "Component.h"
#include "Material.h"

using namespace DirectX;

class Mesh : public Component
{
public:
	Mesh(GameObject* _go, EComponentTypes _type) : Component(_go, _type) {}

	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt);
	void RenderMesh();
	void DeInitMesh();

	//Component Override
	INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) override;
	void StartComponent() override;
	void UpdateComponent() override;
	void DeInitComponent() override;

	void SetMesh(Vertex* _vertecies, const INT _vertsize, USHORT* _indices, const INT _indexsize);
	void RecalculateNormals();
	INT InitializeBuffers(ID3D11Device* _p_d3ddevice);

	Material* MyMaterial = new Material();

private:
	INT InitIndexBuffer(ID3D11Device* _p_d3ddevice);
	INT InitVertexBuffer(ID3D11Device* _p_d3ddevice);
	void InitVertecies(Vertex* _vertecies, INT _size);
	void InitIndices(USHORT* _indices, INT _size);

	ID3D11Buffer* p_vertexBuffer = nullptr;
	ID3D11Buffer* p_indexBuffer = nullptr;

	UINT vertexCount = 0; // Amount of Vertecies
	UINT vertexStride = 0; // Size of one Vertex
	UINT indexCount = 0; // Amount of Indecies

	std::vector<Vertex> vertexData;
	std::vector<USHORT> indexData;

	

	XMFLOAT4X4* worldMatrix = nullptr;

	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
	FLOAT* p_deltaTime = nullptr;
};

XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 _a)
{
	float l = sqrt(_a.x * _a.x + _a.y * _a.y + _a.z * _a.z);

	return XMFLOAT3(_a.x / l, _a.y / l, _a.z / l);
}

XMFLOAT3 SubtractXMFLOT3(XMFLOAT3 _a, XMFLOAT3 _b)
{
	return XMFLOAT3(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z);
}

XMFLOAT3 CrossProductXMFLOAT3(XMFLOAT3 _a, XMFLOAT3 _b)
{
	return XMFLOAT3(_a.y * _b.z - _a.z * _b.y,
					_a.z * _b.x - _a.x * _b.z,
					_a.x * _b.y - _a.y * _b.x);
}

