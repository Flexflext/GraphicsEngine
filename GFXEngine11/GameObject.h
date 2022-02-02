#pragma once
#include "Transform.h"
#include <vector>
#include "Component.h"
#include <type_traits>

enum EComponentTypes
{
	C_Box,
	C_Light,
};

class GameObject
{

	//static_assert(std::is_base_of<Component, T>::value, "type parameter of this class must derive from Component");

public:
	Transform transform = {};

	int Init();
	void Update();
	void DeInit();

	/*template<typename T>
	T GetComponent(EComponentTypes _type);*/

private:
	std::vector<EComponentTypes> allComponents = {};
};

