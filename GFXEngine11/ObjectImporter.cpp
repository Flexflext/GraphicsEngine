#include "ObjectImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void ObjectImporter::Import3DAsset(const char* _p_name, Vertex* _p_vertecies, INT* _p_vertsize, USHORT* _p_indices, INT* _p_indexsize, Mesh* _testmesh)
{
	Assimp::Importer imp;
	const aiScene* p_model = imp.ReadFile(_p_name, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

	const aiMesh* p_mesh = p_model->mMeshes[0];

	*_p_vertsize = p_mesh->mNumVertices;
	_p_vertecies = new Vertex[*_p_vertsize];

	float sizemult = 0.1f;

	for (unsigned int i = 0; i < *_p_vertsize; i++)
	{
		_p_vertecies[i] = { *reinterpret_cast<XMFLOAT3*>(&p_mesh->mVertices[i])};

		if (p_mesh->HasNormals())
		{
			_p_vertecies[i].normal = { *reinterpret_cast<XMFLOAT3*>(&p_mesh->mNormals[i]) };
		}

		if (p_mesh->mTextureCoords[0] != nullptr)
		{
			_p_vertecies[i].uv.x = p_mesh->mTextureCoords[0][i].x;
			_p_vertecies[i].uv.y = p_mesh->mTextureCoords[0][i].y;
		}
	}

	


	*_p_indexsize = p_mesh->mNumFaces * 3;
	_p_indices = new USHORT[*_p_indexsize];

	aiFace& face = p_mesh->mFaces[0];
	for (unsigned int i = 0, j = 0; i < p_mesh->mNumFaces; i++, j+=3)
	{
		face = p_mesh->mFaces[i];
		assert(face.mNumIndices == 3);
		_p_indices[j] = face.mIndices[0];
		_p_indices[j + 1] = face.mIndices[1];
		_p_indices[j + 2] = face.mIndices[2];
	}

	_testmesh->SetMesh(_p_vertecies, *_p_vertsize, _p_indices, *_p_indexsize);
}
