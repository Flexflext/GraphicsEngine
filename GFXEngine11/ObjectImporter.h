#pragma once
#include "Mesh.h"
#include "Vertex.h"

class ObjectImporter
{
public:
	void Import3DAsset(const char* _p_name, Vertex* _p_vertecies, INT* _p_vertsize, USHORT* _p_indices, INT* _p_indexsize, Mesh* _testmesh);
};

