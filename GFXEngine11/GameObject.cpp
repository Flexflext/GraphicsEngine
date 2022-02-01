#include "GameObject.h"
#include "Utils.h"

int GameObject::Init()
{
	INT error = transform.Init();
	CheckError(error);

	return 0;
}

void GameObject::Update()
{
	transform.Update();
}

void GameObject::DeInit()
{
	transform.DeInit();
}
