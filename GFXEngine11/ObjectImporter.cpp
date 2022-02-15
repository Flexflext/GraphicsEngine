#include "ObjectImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void ObjectImporter::Import3DAsset(const char* _p_name, Mesh* _testmesh, USHORT _meshnum)
{
	Assimp::Importer imp;
	const aiScene* p_model = imp.ReadFile(_p_name, aiProcess_Triangulate 
		| aiProcess_JoinIdenticalVertices 
		| aiProcess_FixInfacingNormals 
		| aiProcess_GenUVCoords 
		| aiProcess_CalcTangentSpace 
		| aiProcess_GenNormals 
		| aiProcess_ConvertToLeftHanded
		);

	const aiMesh* p_mesh = p_model->mMeshes[_meshnum];

	INT vertsize = p_mesh->mNumVertices;
	Vertex* p_vertecies = new Vertex[vertsize];

	float sizemult = 0.1f;

	for (unsigned int i = 0; i < vertsize; i++)
	{
		p_vertecies[i] = { *reinterpret_cast<XMFLOAT3*>(&p_mesh->mVertices[i])};

		if (p_mesh->HasNormals())
		{
			p_vertecies[i].normal = { *reinterpret_cast<XMFLOAT3*>(&p_mesh->mNormals[i]) };
		}

		if (p_mesh->mTextureCoords[0] != nullptr)
		{
			p_vertecies[i].uv.x = p_mesh->mTextureCoords[0][i].x;
			p_vertecies[i].uv.y = p_mesh->mTextureCoords[0][i].y;
		}

		if (p_mesh->HasTangentsAndBitangents())
		{
			p_vertecies[i].tangent = { *reinterpret_cast<XMFLOAT3*>(&p_mesh->mTangents[i]) };
			p_vertecies[i].bitangent = { *reinterpret_cast<XMFLOAT3*>(&p_mesh->mBitangents[i]) };
		}
	}


	INT indexsize = p_mesh->mNumFaces * 3;
	USHORT* p_indices = new USHORT[indexsize];

	aiFace& face = p_mesh->mFaces[0];
	for (unsigned int i = 0, j = 0; i < p_mesh->mNumFaces; i++, j+=3)
	{
		face = p_mesh->mFaces[i];
		assert(face.mNumIndices == 3);
		p_indices[j] = face.mIndices[0];
		p_indices[j + 1] = face.mIndices[1];
		p_indices[j + 2] = face.mIndices[2];
	}

	_testmesh->SetMesh(p_vertecies, vertsize, p_indices, indexsize);
}
