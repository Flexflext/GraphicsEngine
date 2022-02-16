#include "Scene.h"
#include "imgui/imgui.h"

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
	ImGui::Begin("GameObjects");
	for (size_t i = 0; i < sceneGameObjects.size(); i++)
	{
		if (ImGui::TreeNode(sceneGameObjects[i]->Name))
		{
			ImGui::Text("Position");
			ImGui::InputFloat("X Pos", &sceneGameObjects[i]->transform.Position.x, 1.0f, 10.0f, "%.1f");
			ImGui::InputFloat("Y Pos", &sceneGameObjects[i]->transform.Position.y, 1.0f, 10.0f, "%.1f");
			ImGui::InputFloat("Z Pos", &sceneGameObjects[i]->transform.Position.z, 1.0f, 10.0f, "%.1f");
			ImGui::Text("Rotation");
			ImGui::InputFloat("X Rot", &sceneGameObjects[i]->transform.Rotation.x, 1.0f, 10.0f, "%.1f");
			ImGui::InputFloat("Y Rot", &sceneGameObjects[i]->transform.Rotation.y, 1.0f, 10.0f, "%.1f");
			ImGui::InputFloat("Z Rot", &sceneGameObjects[i]->transform.Rotation.z, 1.0f, 10.0f, "%.1f");

			ImGui::TreePop();
		}
		
		sceneGameObjects[i]->Update();
	}


	for (GameObject* obj : sceneGameObjects)
	{
		
		obj->Update();
	}
	ImGui::End();
}

void Scene::DeInit()
{
	for (GameObject* obj : sceneGameObjects)
	{
		obj->DeInit();
	}
}

GameObject* Scene::Instantiate(const char* _name)
{
	GameObject* obj = new GameObject(_name);
	sceneGameObjects.push_back(obj);

	return obj;
}

GameObject* Scene::InstantiateAtRuntime()
{
	GameObject* obj = Instantiate("OBJ");

	obj->Awake(p_d3dDevice, p_d3dDeviceContext, p_deltaTime);
	obj->Start();

	return nullptr;
}

void Scene::Destroy(GameObject* _obj)
{
	sceneGameObjects.erase(std::remove(sceneGameObjects.begin(), sceneGameObjects.end(), _obj), sceneGameObjects.end());
	_obj = nullptr;
}
