#pragma once
#include <d3d.h>

#define FVF D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1

struct Vertex
{
	//Position
	FLOAT x;
	FLOAT y;
	FLOAT z;

	//Color
	D3DCOLOR color;

	//UV
	FLOAT u;
	FLOAT v;

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
		color = 0xffffffff;
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

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _u, FLOAT _v)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
		color = 0xffffffff;
		u = _u;
		v = _v;
	}
};