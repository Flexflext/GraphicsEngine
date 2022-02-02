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

//template<typename T>
//T GameObject::GetComponent(EComponentTypes _type) where T : public GameObject
//{
//	for (int i = 0; i < allComponents.size(); i++)
//	{
//		if (allComponents[ i] == _type)
//		{
//			return _type;
//		}
//	}
//}
