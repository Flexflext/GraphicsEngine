#include "GameObject.h"
#include "Mesh.h"
#include "Light.h"

INT GameObject::Awake(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	INT error = transform.Init();
	CheckError(error);

	for (Component* c :  allComponents)
	{
		error = c->AwakeComponent(_p_d3ddevice, _p_d3ddevicecontext, _p_dt);
	}

	return 0;
}

void GameObject::Start()
{
	for (Component* c : allComponents)
	{
		c->StartComponent();
	}
}

void GameObject::Update()
{
	for (Component* c : allComponents)
	{
		c->UpdateComponent();
	}

	transform.Update();
}

void GameObject::DeInit()
{
	for (Component* c : allComponents)
	{
		c->DeInitComponent();
	}

	transform.DeInit();
}

Component* GameObject::AddComponent(EComponentTypes _type)
{
	switch (_type)
	{
	case EComponentTypes::C_Mesh:
	{
		Mesh* mesh = new Mesh(*this, _type);
		allComponents.push_back(mesh);
		return mesh;
		break;
	}
	case EComponentTypes::C_Light:
	{
		Light* light = new Light(*this, _type);
		allComponents.push_back(light);
		return light;
		break;
	}
		break;
	default:
		return nullptr;
		break;
	}

	
}

Component* GameObject::GetComponent(EComponentTypes _type)
{
	for (Component* c : allComponents)
	{
		if (c->CompType == _type)
		{
			return c;
		}
	}

	return nullptr;
}

