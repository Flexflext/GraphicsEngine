#pragma once
#include "Mesh.h"
#include "Vertex.h"

class ObjectImporter
{
public:
	void Import3DAsset(const char* _p_name, Mesh* _testmesh, USHORT _meshnum = 0);
};

