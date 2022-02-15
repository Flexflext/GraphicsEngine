#include "Scene.h"

Scene::Scene(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	p_deltaTime = _p_dt;
	p_d3dDevice = _p_d3ddevice;
	p_d3dDeviceContext = _p_d3ddevicecontext;
}

void Scene::Awake()
{
	for (GameObject* obj : sceneGameObjects)
	{
		obj->Awake(p_d3dDevice, p_d3dDeviceContext, p_deltaTime);
	}
}

void Scene::Start()
{
	for (GameObject* obj : sceneGameObjects)
	{
		obj->Start();
	}
}

void Scene::Update()
{
	for (GameObject* obj : sceneGameObjects)
	{
		obj->Update();
	}
}

void Scene::DeInit()
{
	for (GameObject* obj : sceneGameObjects)
	{
		obj->DeInit();
	}
}

GameObject* Scene::Instantiate()
{
	GameObject* obj = new GameObject();
	sceneGameObjects.push_back(obj);

	return obj;
}

GameObject* Scene::InstantiateAtRuntime()
{
	GameObject* obj = Instantiate();

	obj->Awake(p_d3dDevice, p_d3dDeviceContext, p_deltaTime);
	obj->Start();

	return nullptr;
}

void Scene::Destroy(GameObject* _obj)
{
	sceneGameObjects.erase(std::remove(sceneGameObjects.begin(), sceneGameObjects.end(), _obj), sceneGameObjects.end());
	_obj = nullptr;
}
