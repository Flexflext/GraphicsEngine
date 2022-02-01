#pragma once
#include "Transform.h"

class GameObject
{
public:
	Transform transform = {};

	int Init();
	void Update();
	void DeInit();
};

