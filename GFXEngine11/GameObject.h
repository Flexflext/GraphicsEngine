#pragma once
#include <vector>
#include "Transform.h"
#include "Utils.h"



class Component;
class GameObject
{
public:
	GameObject()
	{
		transform.Init();
	}

	Transform transform;

	INT Awake(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt);
	void Start();
	void Update();
	void DeInit();
	
	Component* AddComponent(EComponentTypes _type);
	Component* GetComponent(EComponentTypes _type);

private:
	std::vector<Component*> allComponents;
};



