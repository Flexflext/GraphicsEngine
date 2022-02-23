//Script to Hold all GameObjects in one place
#pragma once
#include <vector>
#include "GameObject.h"
#include <string>

class Scene
{
public:
	/// <summary>
	/// Give the Scene the the nessesaary Parameters
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <param name="_p_dt"></param>
	Scene(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt);

	/// <summary>
	/// Call Awake on all All GameObjects of the Scene
	/// </summary>
	void Awake();
	/// <summary>
	/// Call Start on all GameObjects of the Scene
	/// </summary>
	void Start();
	/// <summary>
	/// Update all GameObjects in the Scene and Update the UI
	/// </summary>
	void Update();
	/// <summary>
	/// Call DeInitialize the GameObjects
	/// </summary>
	void DeInit();

	/// <summary>
	/// Adds a new GameObject to the Scene
	/// </summary>
	/// <param name="_name">Name of the GameObject for the UI</param>
	/// <returns></returns>
	GameObject* Instantiate(const char* _name);
	/// <summary>
	/// Initialize the Given GameObjects
	/// </summary>
	/// <param name="_toinit">GameObject to Initialize</param>
	void InitialzeGameObject(GameObject* _toinit);
	/// <summary>
	/// Deinititialize and Remove from sceneGameObjects List
	/// </summary>
	/// <param name="_obj"></param>
	void Destroy(GameObject* _obj);

private:
	//All GameObjects in the Scene
	std::vector<GameObject*> sceneGameObjects = {};

	ID3D11Device* p_d3dDevice = nullptr;
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
	FLOAT* p_deltaTime = nullptr;
	std::string name;
};

