#include "ObjectImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ObjectImporter* ObjectImporter::Instance = nullptr;


ObjectImporter* ObjectImporter::GetInstance()
{
	//Check if Already Existant
	if (Instance == nullptr) Instance = new ObjectImporter();

	return Instance;
}

void ObjectImporter::Import3DAsset(const char* _p_name, Mesh* _mesh, USHORT _meshnum, float _size)
{
	//Set Importer
	Assimp::Importer imp;

	//Load Model at Path and Set Importing Flags
	const aiScene* p_model = imp.ReadFile(_p_name,
		  aiProcess_Triangulate // -> Only Tris
		| aiProcess_JoinIdenticalVertices // -> Less Vertices
		| aiProcess_FixInfacingNormals // -> Good Normals
		| aiProcess_GenUVCoords // -> Generate UV Coordinates
		| aiProcess_CalcTangentSpace // -> Calculate Tangents and Bitangents
		| aiProcess_GenNormals // -> Generate Normals
		| aiProcess_ConvertToLeftHanded // -> Convert to Left Handed
		);

	//Set Mesh to the number that the user Wants to import
	const aiMesh* p_mesh = p_model->mMeshes[_meshnum];

	//Set Vertecies and Array
	INT vertsize = p_mesh->mNumVertices;
	Vertex* p_vertecies = new Vertex[vertsize];

	//Load Vertex Data
	for (unsigned int i = 0; i < vertsize; i++)
	{
		//Set Positions
		p_vertecies[i].position.x = p_mesh->mVertices[i].x * _size;
		p_vertecies[i].position.y = p_mesh->mVertices[i].y * _size;
		p_vertecies[i].position.z = p_mesh->mVertices[i].z * _size;

		//Set Normals
		if (p_mesh->HasNormals())
		{
			p_vertecies[i].normal = { *reinterpret_cast<XMFLOAT3*>(&p_mesh->mNormals[i]) };
		}

		//Set UVs
		if (p_mesh->mTextureCoords[0] != nullptr)
		{
			p_vertecies[i].uv.x = p_mesh->mTextureCoords[0][i].x;
			p_vertecies[i].uv.y = p_mesh->mTextureCoords[0][i].y;
		}

		//Set Bitangents and Tangents
		if (p_mesh->HasTangentsAndBitangents())
		{
			p_vertecies[i].tangent = { *reinterpret_cast<XMFLOAT3*>(&p_mesh->mTangents[i]) };
			p_vertecies[i].bitangent = { *reinterpret_cast<XMFLOAT3*>(&p_mesh->mBitangents[i]) };
		}
	}

	//Set Index Size and Array Size
	INT indexsize = p_mesh->mNumFaces * 3;
	USHORT* p_indices = new USHORT[indexsize];

	//Load Indices
	aiFace& face = p_mesh->mFaces[0];
	for (unsigned int i = 0, j = 0; i < p_mesh->mNumFaces; i++, j+=3)
	{
		face = p_mesh->mFaces[i];
		assert(face.mNumIndices == 3);
		p_indices[j] = face.mIndices[0];
		p_indices[j + 1] = face.mIndices[1];
		p_indices[j + 2] = face.mIndices[2];
	}

	//Give Mesh the Data
	_mesh->SetMesh(p_vertecies, vertsize, p_indices, indexsize);
}
