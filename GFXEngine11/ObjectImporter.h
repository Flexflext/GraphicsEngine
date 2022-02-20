#pragma once
#include "Mesh.h"
#include "Vertex.h"

class ObjectImporter
{
public:
	ObjectImporter(ObjectImporter& other) = delete;
	void operator=(const ObjectImporter&) = delete;

	static ObjectImporter* GetInstance();

	void Import3DAsset(const char* _p_name, Mesh* _testmesh, USHORT _meshnum = 0, float _size = 1);

private:
	static ObjectImporter* Instance;

	ObjectImporter()
	{

	}
};

