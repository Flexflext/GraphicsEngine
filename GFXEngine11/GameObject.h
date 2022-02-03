#pragma once
#include <vector>
#include "Transform.h"
#include "Utils.h"

class Component;
class GameObject
{
public:
	Transform transform;

	INT Init();
	void Update();
	void DeInit();
	
	Component* AddComponent(EComponentTypes _type);
	Component* GetComponent(EComponentTypes _type);

private:
	std::vector<Component*> allComponents;
};



