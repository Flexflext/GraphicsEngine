#include "Transform.h"

INT Transform::Init()
{
	//Initialize World Transformation-Matrix
	XMStoreFloat4x4(WorldMatrix, XMMatrixIdentity());

	return 0;
}

void Transform::Update()
{
	TranslationMatrix = XMMatrixTranslation(Position.x, Position.y, Position.z);
	RotationMatrix = XMMatrixRotationRollPitchYaw(Rotation.x / 57.29578f, Rotation.y / 57.29578f, Rotation.z / 57.29578f);
	LocalScaleMatrix = XMMatrixScaling(Scale.x, Scale.y, Scale.z);

	XMStoreFloat4x4(WorldMatrix, LocalScaleMatrix * RotationMatrix * TranslationMatrix);
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

void Transform::AddPosition(FLOAT _x, FLOAT _y, FLOAT _z)
{
	Position.x += _x;
	Position.y += _y;
	Position.z += _z;
}

void Transform::AddRotation(FLOAT _x, FLOAT _y, FLOAT _z)
{
	Rotation.x += _x;
	Rotation.y += _y;
	Rotation.z += _z;
}

void Transform::AddScale(FLOAT _x, FLOAT _y, FLOAT _z)
{
	Scale.x += _x;
	Scale.y += _y;
	Scale.z += _z;
}
