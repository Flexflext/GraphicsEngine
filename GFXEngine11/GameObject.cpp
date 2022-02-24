#include "GameObject.h"
#include "Component.h"
#include "Utils.h"

INT GameObject::Awake(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	INT error;
	for (Component* c :  allComponents)
	{
		//Awake Component
		error = c->AwakeComponent(_p_d3ddevice, _p_d3ddevicecontext, _p_dt);
		CheckIntError(error);
	}

	return 0;
}

void GameObject::Start()
{
	for (Component* c : allComponents)
	{
		//Start Component
		c->StartComponent();
	}
}

void GameObject::Update()
{
	//Check if GameObject is Active to Update te GameObject
	if (IsActive)
	{
		//Update the Transform
		transform.Update();

		for (Component* c : allComponents)
		{
			//Check if Component is Active
			if (c->IsActive)
			{
				c->UpdateComponent();
			}
		}
	}
}

void GameObject::DeInit()
{
	for (Component* c : allComponents)
	{
		//Deinit the Component
		c->DeInitComponent();
	}

	//Deinit the Transform
	transform.DeInit();
}


