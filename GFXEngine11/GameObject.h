#pragma once
#include <vector>
#include "Transform.h"
#include "Utils.h"

class Component;
class GameObject
{
public:
	GameObject(const char* _name)
	{
		Name = _name;

		transform.Init();
	}

	Transform transform;

	INT Awake(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt);
	void Start();
	void Update();
	void DeInit();
	
	Component* AddComponent(EComponentTypes _type);

	template<typename T>
	T* GetComponent();

	bool IsActive = true;

	const char* Name;

private:
	std::vector<Component*> allComponents;
};

template<typename T>
T* GameObject::GetComponent()
{
	for (Component* c : allComponents)
	{
		if (dynamic_cast<T*>(c) != nullptr)
		{
			return c;
		}
	}

	return nullptr;
}


