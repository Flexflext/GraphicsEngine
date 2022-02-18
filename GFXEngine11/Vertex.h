#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct Vertex
{
public:
	// Position
	XMFLOAT3 position;
	// Normal
	XMFLOAT3 normal;
	//UV
	XMFLOAT2 uv;

	XMFLOAT3 tangent;

	XMFLOAT3 bitangent;
	
	Vertex()
	{

	}

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		uv.x = 0;
		uv.x = 0;
		/*color.x = 1;
		color.y = 1;
		color.z = 1;
		color.w = 1;*/
	}

	Vertex(XMFLOAT3 _pos)
	{
		position = _pos;
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		uv.x = 0;
		uv.y = 0;
		/*color.x = 1;
		color.y = 1;
		color.z = 1;
		color.w = 1;*/
	}

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, UINT _r, UINT _g, UINT _b)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		uv.x = 0;
		uv.x = 0;
		/*color.x = _r / 255.0f;
		color.y = _g / 255.0f;
		color.z = _b / 255.0f;
		color.w = 1;*/
	}

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _u, FLOAT _v)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		uv.x = _u;
		uv.x = _v;
		/*color.x = 1;
		color.y = 1;
		color.z = 1;
		color.w = 1;*/
	}

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _nx, FLOAT _ny, FLOAT _nz, FLOAT _u, FLOAT _v)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
		normal.x = _nx;
		normal.y = _ny;
		normal.z = _nz;
		uv.x = _u;
		uv.x = _v;
		/*color.x = 1;
		color.y = 1;
		color.z = 1;
		color.w = 1;*/
	}
};