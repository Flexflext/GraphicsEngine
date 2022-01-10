#pragma once
#include <d3d.h>

#define FVF D3DFVF_XYZ | D3DFVF_DIFFUSE

struct Vertex
{
	//Position
	FLOAT x;
	FLOAT y;
	FLOAT z;

	//Color
	D3DCOLOR color;

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, D3DCOLOR _color)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;

		this->color = _color;
	}

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, UINT _r, UINT _g, UINT _b)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;

		this->color = D3DCOLOR_XRGB(_r, _g, _b);
	}
};