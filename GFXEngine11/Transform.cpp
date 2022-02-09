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

	XMVECTOR localUp = XMVector3TransformCoord(XMVectorSet(0, 1, 0, 0), RotationMatrix);
	XMVECTOR localRight = XMVector3TransformCoord(XMVectorSet(1, 0, 0, 0), RotationMatrix);
	XMVECTOR localForward = XMVector3TransformCoord(XMVectorSet(0, 0, 1, 0), RotationMatrix);

	LocalUp.x = XMVectorGetX(localUp);
	LocalUp.y = XMVectorGetY(localUp);
	LocalUp.z = XMVectorGetZ(localUp);

	LocalRight.x = XMVectorGetX(localRight);
	LocalRight.y = XMVectorGetY(localRight);
	LocalRight.z = XMVectorGetZ(localRight);

	LocalForward.x = XMVectorGetX(localForward);
	LocalForward.y = XMVectorGetY(localForward);
	LocalForward.z = XMVectorGetZ(localForward);

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
