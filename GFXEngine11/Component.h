#pragma once
#include "Utils.h"
#include "GameObject.h"


class Component
{
public:

	Component()
	{
			
	}

	Component(GameObject _go, EComponentTypes _comptype)
	{
		gameObject = _go;
	}

	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void DeInit() {};
	EComponentTypes CompType;

protected:
	GameObject gameObject;
};

