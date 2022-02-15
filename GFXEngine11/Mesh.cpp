#include "Mesh.h"

using namespace DirectX;

INT Mesh::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	p_d3dDeviceContext = _p_d3ddevicecontext;
	p_deltaTime = _p_dt;

	INT error = InitializeBuffers(_p_d3ddevice);
	CheckIntError(error);

	return 0;
}

void Mesh::RenderMesh()
{
	//Set Mesh Data
	static UINT offset = 0;
	p_d3dDeviceContext->IASetVertexBuffers(0, 1, &p_vertexBuffer, &vertexStride, &offset);
	p_d3dDeviceContext->IASetIndexBuffer(p_indexBuffer, DXGI_FORMAT_R16_UINT, offset);
	p_d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Draw With Index Buffer
	p_d3dDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void Mesh::DeInitMesh()
{
	SafeRelease<ID3D11Buffer>(p_vertexBuffer);
	SafeRelease<ID3D11Buffer>(p_indexBuffer);
	SafeRelease<ID3D11DeviceContext>(p_d3dDeviceContext);
}

INT Mesh::InitVertexBuffer(ID3D11Device* _p_d3ddevice)
{
	Vertex* vertecies = new Vertex[vertexData.size()];
	std::copy(vertexData.begin(), vertexData.end(), vertecies);

	vertexCount = std::size(vertexData);
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

void Mesh::InitVertecies(Vertex* _vertecies, INT _size)
{
	if (_vertecies !=  nullptr)
	{
		vertexData.reserve(_size);

		for (int i = 0; i < _size + 1; i++)
		{
			vertexData.push_back(_vertecies[i]);
		}
	}
	else
	{
		Vertex vertecies[] = {
			//Front
			Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f), // 0
			Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f), // 1
			Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f), // 2
			Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f), // 3

			//Back
			Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f), // 4
			Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f), // 5
			Vertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f), // 6
			Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f), // 7

			//Top
			Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f), // 1 // 8
			Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f), // 5 // 9
			Vertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f), // 6 // 10
			Vertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f), // 2 // 11

			//Bottom
			Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f), // 4 // 12
			Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f), // 0 // 13
			Vertex(0.5f, -0.5f, -0.5f, 1.0f, 1.0f), // 3 // 14
			Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f), // 7 // 15

			//Left
			Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f), // 4 // 16
			Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f), // 5 // 17
			Vertex(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f), // 1 // 18
			Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f), // 0 // 19

			//Right
			Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f), // 3 // 20
			Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f), // 2 // 21
			Vertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f), // 6 // 22
			Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f), // 7 // 23
		};

		vertexData.reserve(std::size(vertecies));

		for (int i = 0; i < std::size(vertecies); i++)
		{
			vertexData.push_back(vertecies[i]);
		}
	}
}

void Mesh::InitIndices(USHORT* _indices, INT _size)
{
	if (_indices != nullptr)
	{
		indexData.reserve(_size);

		for (int i = 0; i < _size + 1; i++)
		{
			indexData.push_back(_indices[i]);
		}
	}
	else
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

		indexData.reserve(std::size(indices));

		for (int i = 0; i < std::size(indices); i++)
		{
			indexData.push_back(indices[i]);
		}
	}
}

INT Mesh::InitIndexBuffer(ID3D11Device* _p_d3ddevice)
{
	USHORT* indices = new USHORT[indexData.size()];
	std::copy(indexData.begin(), indexData.end(), indices);

	indexCount = std::size(indexData);

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

void Mesh::SetMesh(Vertex* _vertecies, INT _vertsize, USHORT* _indices, INT _indexsize)
{
	vertexData.clear();
	indexData.clear();

	InitVertecies(_vertecies, _vertsize);
	InitIndices(_indices, _indexsize);
}

void Mesh::RecalculateNormals()
{
	USHORT size = indexData.size() - 1;

	for (size_t i = 0; i < size; i += 3)
	{
		USHORT indexA = indexData[i];
		USHORT indexB = indexData[i + 1];
		USHORT indexC = indexData[i + 2];

		XMFLOAT3 Normalized = NormalizeXMFLOAT3(CrossProductXMFLOAT3(SubtractXMFLOT3(vertexData[indexB].position, vertexData[indexA].position), SubtractXMFLOT3(vertexData[indexC].position, vertexData[indexA].position)));

		vertexData[indexA].normal = Normalized;
		vertexData[indexB].normal = Normalized;
		vertexData[indexC].normal = Normalized;
	}
}

INT Mesh::InitializeBuffers(ID3D11Device* _p_d3ddevice)
{
	INT error = InitVertexBuffer(_p_d3ddevice);
	CheckIntError(error);

	error = InitIndexBuffer(_p_d3ddevice);
	CheckIntError(error);

	return 0;
}


INT Mesh::AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	INT error = MyMaterial->Init(_p_d3ddevice, _p_d3ddevicecontext);
	CheckIntError(error); 

	error = Init(_p_d3ddevice, _p_d3ddevicecontext, _p_dt);
	CheckIntError(error); 
}

void Mesh::StartComponent()
{
	worldMatrix = gameObject->transform.WorldMatrix;
	MyMaterial->InitMatrices(worldMatrix);
}

void Mesh::UpdateComponent()
{
	MyMaterial->Render();
	RenderMesh();
}

void Mesh::DeInitComponent()
{
	MyMaterial->DeInit();
	DeInitMesh();
}
