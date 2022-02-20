#pragma once
#include <vector>
#include "GameObject.h"
#include <string>

class Scene
{
public:
	Scene(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt);

	void Awake();
	void Start();
	void Update();
	void DeInit();

	GameObject* Instantiate(const char* _name);
	void InitialzeGameObject(GameObject* _toinit);
	void Destroy(GameObject* _obj);

private:
	std::vector<GameObject*> sceneGameObjects = {};

	ID3D11Device* p_d3dDevice = nullptr;
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
	FLOAT* p_deltaTime = nullptr;
	std::string name;
};

