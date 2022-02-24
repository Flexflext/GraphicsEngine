//Mesh Component for GameObjects
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
	Mesh(GameObject* _go) : Component(_go)
	{ 
		//Set a Base Mesh for the Component
		SetMesh(nullptr, 0, nullptr, 0); 
		//Calculate the Normals of the Mesh
		RecalculateNormals();
	}

	/// <summary>
	/// Initialize the Mesh Component
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <param name="_p_dt"></param>
	/// <returns></returns>
	INT Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt);
	/// <summary>
	/// Render and Update the Mesh
	/// </summary>
	void RenderMesh();
	/// <summary>
	/// Deinitialize the Mesh
	/// </summary>
	void DeInitMesh();

	/// <summary>
	/// Set the Material Type of the Mesh Component
	/// </summary>
	/// <param name="_p_properties"></param>
	void SetMaterial(MaterialProperties* _p_properties);
	/// <summary>
	/// Load a Mesh from a File
	/// </summary>
	/// <param name="_p_name">File Path of the Mesh</param>
	/// <param name="_nummesh">Number of the Mesh</param>
	/// <param name="_size">Set the Import Size of the Mesh</param>
	void LoadMesh(const char* _p_name, USHORT _nummesh = 0, float _size = 1);
	/// <summary>
	/// Set a Mesh of the with a Vertecies and Indices Array Pointer
	/// </summary>
	/// <param name="_vertecies"></param>
	/// <param name="_vertsize"></param>
	/// <param name="_indices"></param>
	/// <param name="_indexsize"></param>
	void SetMesh(Vertex* _vertecies, const INT _vertsize, USHORT* _indices, const INT _indexsize);
	/// <summary>
	/// Recalculate the Normals of the CUrrent Mesh of this Component
	/// </summary>
	void RecalculateNormals();
	

	//Component Override Methoden
	INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) override;
	void StartComponent() override;
	void UpdateComponent() override;
	void DeInitComponent() override;


private:
	/// <summary>
	/// Initialize the Indices and Vertices Buffer
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <returns></returns>
	INT InitializeBuffers(ID3D11Device* _p_d3ddevice);
	/// <summary>
	/// Initialize the IndexBuffer 
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <returns></returns>
	INT InitIndexBuffer(ID3D11Device* _p_d3ddevice);
	/// <summary>
	/// Initialize the Vertex Buffer
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <returns></returns>
	INT InitVertexBuffer(ID3D11Device* _p_d3ddevice);
	/// <summary>
	/// Initialize the Vertecies Array
	/// </summary>
	/// <param name="_vertecies"></param>
	/// <param name="_size"></param>
	void InitVertecies(Vertex* _vertecies, INT _size);
	/// <summary>
	/// Initiliaze the Indices Array
	/// </summary>
	/// <param name="_indices"></param>
	/// <param name="_size"></param>
	void InitIndices(USHORT* _indices, INT _size);

	Material* myMaterial = new Material(); // -> Material of this Mesh
	ID3D11Buffer* p_vertexBuffer = nullptr; // -> VertexBuffer
	ID3D11Buffer* p_indexBuffer = nullptr; // -> IndexBuffer

	UINT vertexCount = 0; // Amount of Vertecies
	UINT vertexStride = 0; // Size of one Vertex
	UINT indexCount = 0; // Amount of Indecies

	std::vector<Vertex> vertexData; // Vertecies Array
	std::vector<USHORT> indexData; // Indices Array

	XMFLOAT4X4* worldMatrix = nullptr; // -> WorldMatrix -> has to be in Mesh Class

	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
	FLOAT* p_deltaTime = nullptr;
};

/// <summary>
/// Normalizees a XMFLOAT3
/// </summary>
/// <param name="_a"></param>
/// <returns></returns>
XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 _a)
{
	float l = sqrt(_a.x * _a.x + _a.y * _a.y + _a.z * _a.z);

	return XMFLOAT3(_a.x / l, _a.y / l, _a.z / l);
}

/// <summary>
/// Subtract a XMFLOAT3 from another XMFLOAT3
/// </summary>
/// <param name="_a"></param>
/// <param name="_b"></param>
/// <returns></returns>
XMFLOAT3 SubtractXMFLOT3(XMFLOAT3 _a, XMFLOAT3 _b)
{
	return XMFLOAT3(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z);
}

/// <summary>
/// Calculate the Cross Product of two XMFLOAT3s
/// </summary>
/// <param name="_a"></param>
/// <param name="_b"></param>
/// <returns></returns>
XMFLOAT3 CrossProductXMFLOAT3(XMFLOAT3 _a, XMFLOAT3 _b)
{
	return XMFLOAT3(_a.y * _b.z - _a.z * _b.y,
					_a.z * _b.x - _a.x * _b.z,
					_a.x * _b.y - _a.y * _b.x);
}

