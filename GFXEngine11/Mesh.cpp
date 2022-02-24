#include "Mesh.h"
#include "ObjectImporter.h"

using namespace DirectX;



INT Mesh::Init(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	//Set DeviceContext and DeltaTime
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
	//Set Vertex Buffer
	p_d3dDeviceContext->IASetVertexBuffers(0, 1, &p_vertexBuffer, &vertexStride, &offset);
	//Set Index Buffer
	p_d3dDeviceContext->IASetIndexBuffer(p_indexBuffer, DXGI_FORMAT_R16_UINT, offset);
	//Set Topology
	p_d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Draw With Index Buffer
	p_d3dDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void Mesh::DeInitMesh()
{
	//Release Com Objects
	SafeRelease<ID3D11Buffer>(p_vertexBuffer);
	SafeRelease<ID3D11Buffer>(p_indexBuffer);
	SafeRelease<ID3D11DeviceContext>(p_d3dDeviceContext);
}

INT Mesh::InitVertexBuffer(ID3D11Device* _p_d3ddevice)
{
	//Set Vertecies Array to Give to Buffer
	Vertex* vertecies = new Vertex[vertexData.size()];
	std::copy(vertexData.begin(), vertexData.end(), vertecies);

	vertexCount = std::size(vertexData);
	vertexStride = sizeof(Vertex);

	//Set Description
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = vertexCount * vertexStride;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE; // who has wich access

	//Set Init Data 
	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = vertecies;

	//Set Buffer
	HRESULT hr = _p_d3ddevice->CreateBuffer(&desc, &initialData, &p_vertexBuffer);
	CheckFailed(hr, 30);


	return 0;
}

void Mesh::InitVertecies(Vertex* _vertecies, INT _size)
{
	//Check if Nullptr to Check if to Use array or Base Mesh
	if (_vertecies !=  nullptr)
	{
		//Set Mesh Vertex Data Array
		vertexData.reserve(_size);

		for (int i = 0; i < _size + 1; i++)
		{
			vertexData.push_back(_vertecies[i]);
		}
	}
	else
	{
		//Set Base Mesh Vertecies Array
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

		//Set Mes Vertex Data Array
		vertexData.reserve(std::size(vertecies));

		for (int i = 0; i < std::size(vertecies); i++)
		{
			vertexData.push_back(vertecies[i]);
		}
	}
}

void Mesh::InitIndices(USHORT* _indices, INT _size)
{
	//Check if to use base Mesh Indices
	if (_indices != nullptr)
	{
		//Set Indices array
		indexData.reserve(_size);

		for (int i = 0; i < _size + 1; i++)
		{
			indexData.push_back(_indices[i]);
		}
	}
	else
	{
		//Set Base Mesh Array
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
	//Set indices Array
	USHORT* indices = new USHORT[indexData.size()];
	std::copy(indexData.begin(), indexData.end(), indices);

	indexCount = std::size(indexData);

	//Set Buffer Description
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = indexCount * sizeof(USHORT);
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE; // who has wich access

	//Set Initial Data
	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = indices;

	//Create Buffer
	HRESULT hr = _p_d3ddevice->CreateBuffer(&desc, &initialData, &p_indexBuffer);
	CheckFailed(hr, 32);

	return 0;
}

void Mesh::SetMaterial(MaterialProperties* _p_properties)
{
	//Set base Material
	myMaterial->SetMaterial(_p_properties);
}

void Mesh::LoadMesh(const char* _p_name, USHORT _nummesh, float _size)
{
	//Load Mesh from the ObjectImporter
	ObjectImporter::GetInstance()->Import3DAsset(_p_name, this, _nummesh, _size);
}

void Mesh::SetMesh(Vertex* _vertecies, INT _vertsize, USHORT* _indices, INT _indexsize)
{
	//Clear Previous Data
	vertexData.clear();
	indexData.clear();

	//Initial Data
	InitVertecies(_vertecies, _vertsize);
	InitIndices(_indices, _indexsize);
}

void Mesh::RecalculateNormals()
{
	USHORT size = indexData.size() - 1;

	//Calculate new Face Data
	for (size_t i = 0; i < size; i += 3)
	{
		USHORT indexA = indexData[i];
		USHORT indexB = indexData[i + 1];
		USHORT indexC = indexData[i + 2];
		
		//Calculate Normal
		XMFLOAT3 Normalized = NormalizeXMFLOAT3(CrossProductXMFLOAT3(SubtractXMFLOT3(vertexData[indexB].position, vertexData[indexA].position), SubtractXMFLOT3(vertexData[indexC].position, vertexData[indexA].position)));

		//Set Normals 
		vertexData[indexA].normal = Normalized;
		vertexData[indexB].normal = Normalized;
		vertexData[indexC].normal = Normalized;
	}
}

INT Mesh::InitializeBuffers(ID3D11Device* _p_d3ddevice)
{
	//Inittialize Vertex Buffer
	INT error = InitVertexBuffer(_p_d3ddevice);
	CheckIntError(error);

	//Initialize Index Buffer
	error = InitIndexBuffer(_p_d3ddevice);
	CheckIntError(error);

	return 0;
}

INT Mesh::AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	//Initiliaze the Material
	INT error = myMaterial->Init(_p_d3ddevice, _p_d3ddevicecontext, gameObject->transform.WorldMatrix);
	CheckIntError(error); 

	//Initialize the Mesh
	error = Init(_p_d3ddevice, _p_d3ddevicecontext, _p_dt);
	CheckIntError(error); 
}

void Mesh::StartComponent()
{
	//Set WorldMatrix
	worldMatrix = gameObject->transform.WorldMatrix;
}

void Mesh::UpdateComponent()
{
	//Render Material and Mesh
	myMaterial->Render();
	RenderMesh();
}

void Mesh::DeInitComponent()
{
	//DeInitialize the Material and Mesh
	myMaterial->DeInit();
	DeInitMesh();
}
