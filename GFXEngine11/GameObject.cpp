#include "GameObject.h"
#include "Mesh.h"
#include "Light.h"

INT GameObject::Init()
{
	INT error = transform.Init();
	CheckError(error);

	for (Component* c :  allComponents)
	{
		c->Awake();
	}

	for (Component* c : allComponents)
	{
		c->Start();
	}

	return 0;
}

void GameObject::Update()
{
	for (Component* c : allComponents)
	{
		c->Update();
	}

	transform.Update();
}

void GameObject::DeInit()
{
	for (Component* c : allComponents)
	{
		c->DeInit();
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
	Component* toget = nullptr;

	switch (_type)
	{
	case EComponentTypes::C_Mesh:
		break;
	case EComponentTypes::C_Light:
		break;
	}

	return toget;
}

//Component GameObject::GetComponent(EComponentTypes _type)
//{
//	return Component();
//}

