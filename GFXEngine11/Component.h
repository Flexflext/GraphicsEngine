#pragma once
#include "Utils.h"
#include "GameObject.h"


class Component
{
public:

	Component()
	{
			
	}

	Component(GameObject* _go, EComponentTypes _comptype)
	{
		gameObject = _go;
	}

	virtual INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) { return 0; };
	virtual void StartComponent() {};
	virtual void UpdateComponent() {};
	virtual void DeInitComponent() {};
	EComponentTypes CompType;

	GameObject* gameObject;

	bool IsActive = true;
};

