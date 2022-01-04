#pragma once
#include <d3d.h>

#define FVF D3DFVF_XYZ

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}
};