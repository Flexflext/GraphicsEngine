// Object Importer to Load Meshes from Files with the Assimp Importer
#pragma once
#include "Mesh.h"
#include "Vertex.h"

class ObjectImporter
{
public:
	//Singelton Logic
	ObjectImporter(ObjectImporter& other) = delete;
	void operator=(const ObjectImporter&) = delete;

	/// <summary>
	/// Get Instance of the ObjectImporter
	/// </summary>
	/// <returns></returns>
	static ObjectImporter* GetInstance();

	/// <summary>
	/// Import a 3D Asset and Load and Set the Mesh
	/// </summary>
	/// <param name="_p_name"></param>
	/// <param name="_testmesh"></param>
	/// <param name="_meshnum"></param>
	/// <param name="_size"></param>
	void Import3DAsset(const char* _p_name, Mesh* _testmesh, USHORT _meshnum = 0, float _size = 1);

private:
	//Singelton Instance
	static ObjectImporter* Instance;

	//Only Private Construction
	ObjectImporter()
	{

	}
};

