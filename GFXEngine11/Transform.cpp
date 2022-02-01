#include "Transform.h"

INT Transform::Init()
{
	//Initialize World Transformation-Matrix
	XMStoreFloat4x4(&WorldMatrix, XMMatrixIdentity());

	return 0;
}

void Transform::Update()
{
	XMMATRIX translation = XMMatrixTranslation(Position.x, Position.y, Position.z);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z);
	XMMATRIX localScale = XMMatrixScaling(Scale.x, Scale.y, Scale.z);

	XMStoreFloat4x4(&WorldMatrix, localScale * rotation * translation);
}

INT Transform::DeInit()
{
	return 0;
}

void Transform::SetPosition(FLOAT _x, FLOAT _y, FLOAT _z)
{
	Position.x = _x;
	Position.y = _y;
	Position.z = _z;
}

void Transform::SetRotation(FLOAT _x, FLOAT _y, FLOAT _z)
{
	Rotation.x = _x;
	Rotation.y = _y;
	Rotation.z = _z;
}

void Transform::SetScale(FLOAT _x, FLOAT _y, FLOAT _z)
{
	Scale.x = _x;
	Scale.y = _y;
	Scale.z = _z;
}
