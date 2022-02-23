//Component Base Class
#pragma once
#include "Utils.h"
#include "GameObject.h"


class Component
{
public:

	Component()
	{
			
	}

	Component(GameObject* _go)
	{
		gameObject = _go;
	}

	/// <summary>
	/// Awake the Component -> Pure Virtual Function (Only Child Class will be Called)
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <param name="_p_dt"></param>
	/// <returns></returns>
	virtual INT AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt) = 0;
	/// <summary>
	/// Start the Component -> Pure Virtual Function (Only Child Class will be Called)
	/// </summary>
	virtual void StartComponent() = 0;
	/// <summary>
	/// Update the Component -> Pure Virtual Function (Only Child Class will be Called)
	/// </summary>
	virtual void UpdateComponent() = 0;
	/// <summary>
	/// Deinittialize the Component -> Pure Virtual Function (Only Child Class will be Called)
	/// </summary>
	virtual void DeInitComponent() = 0;

	GameObject* gameObject;

	bool IsActive = true;
};

