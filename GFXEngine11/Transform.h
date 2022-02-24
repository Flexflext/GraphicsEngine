//Transform Component for all GameObejcts
#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
public:
	Transform()
	{
		Scale.x = 1;
		Scale.y = 1;
		Scale.z = 1;
	}

	

	/// <summary>
	/// Initializes the Transform Component of a GameObject
	/// </summary>
	/// <returns></returns>
	INT Init();
	/// <summary>
	/// Update the Transform Component
	/// </summary>
	void Update();
	/// <summary>
	/// Deinitializes the Transform Component
	/// </summary>
	/// <returns></returns>
	INT DeInit();
	
	/// <summary>
	/// Set a Specific Position
	/// </summary>
	/// <param name="_x"></param>
	/// <param name="_y"></param>
	/// <param name="_z"></param>
	void SetPosition(FLOAT _x, FLOAT _y, FLOAT _z);
	/// <summary>
	/// Set a Specific Rotation
	/// </summary>
	/// <param name="_x"></param>
	/// <param name="_y"></param>
	/// <param name="_z"></param>
	void SetRotation(FLOAT _x, FLOAT _y, FLOAT _z);
	/// <summary>
	/// Set the Scale
	/// </summary>
	/// <param name="_x"></param>
	/// <param name="_y"></param>
	/// <param name="_z"></param>
	void SetScale(FLOAT _x, FLOAT _y, FLOAT _z);
	/// <summary>
	/// Add a Position to the existing Position
	/// </summary>
	/// <param name="_x"></param>
	/// <param name="_y"></param>
	/// <param name="_z"></param>
	void AddPosition(FLOAT _x, FLOAT _y, FLOAT _z);
	/// <summary>
	/// Add a Rotatation to the existing Rotation
	/// </summary>
	/// <param name="_x"></param>
	/// <param name="_y"></param>
	/// <param name="_z"></param>
	void AddRotation(FLOAT _x, FLOAT _y, FLOAT _z);
	/// <summary>
	/// Add a Scale to the current Scale
	/// </summary>
	/// <param name="_x"></param>
	/// <param name="_y"></param>
	/// <param name="_z"></param>
	void AddScale(FLOAT _x, FLOAT _y, FLOAT _z);

	//Tranformation Paramters
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;

	//Local Direction Paramters
	XMFLOAT3 LocalUp = { 0,1,0 };
	XMFLOAT3 LocalRight = { 1,0,0 };
	XMFLOAT3 LocalForward = { 0,0,1 };

	//Matrices
	XMMATRIX TranslationMatrix;
	XMMATRIX RotationMatrix;
	XMMATRIX LocalScaleMatrix;

	XMFLOAT4X4* WorldMatrix = new XMFLOAT4X4();

private:
	XMVECTOR localUp;
	XMVECTOR localRight;
	XMVECTOR localForward;
};

