#include "Scene.h"
#include "imgui/imgui.h"


Scene::Scene(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	//Set the Parameters
	p_deltaTime = _p_dt;
	p_d3dDevice = _p_d3ddevice;
	p_d3dDeviceContext = _p_d3ddevicecontext;
}

void Scene::Awake()
{
	//Awake the GameObjects
	for (GameObject* obj : sceneGameObjects)
	{
		obj->Awake(p_d3dDevice, p_d3dDeviceContext, p_deltaTime);
	}
}

void Scene::Start()
{
	//Start the GameObjects
	for (GameObject* obj : sceneGameObjects)
	{
		obj->Start();
	}
}

void Scene::Update()
{
	//Update the Scene UI
	ImGui::Begin("GameObjects");
	for (size_t i = 0; i < sceneGameObjects.size(); i++)
	{
		//Set the Name with a number in the List
		name = std::to_string(i).c_str();
		name += " ";
		name += sceneGameObjects[i]->Name;

		//Update UI -> Interactable
		if (ImGui::TreeNode(name.c_str()))
		{
			if (ImGui::TreeNode("Position"))
			{
				ImGui::InputFloat("X", &sceneGameObjects[i]->transform.Position.x, 1.0f, 10.0f, "%.1f");
				ImGui::InputFloat("Y", &sceneGameObjects[i]->transform.Position.y, 1.0f, 10.0f, "%.1f");
				ImGui::InputFloat("Z", &sceneGameObjects[i]->transform.Position.z, 1.0f, 10.0f, "%.1f");
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Rotation"))
			{
				ImGui::InputFloat("X", &sceneGameObjects[i]->transform.Rotation.x, 1.0f, 10.0f, "%.1f");
				ImGui::InputFloat("Y", &sceneGameObjects[i]->transform.Rotation.y, 1.0f, 10.0f, "%.1f");
				ImGui::InputFloat("Z", &sceneGameObjects[i]->transform.Rotation.z, 1.0f, 10.0f, "%.1f");
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Scale"))
			{
				ImGui::InputFloat("X", &sceneGameObjects[i]->transform.Scale.x, 1.0f, 10.0f, "%.1f");
				ImGui::InputFloat("Y", &sceneGameObjects[i]->transform.Scale.y, 1.0f, 10.0f, "%.1f");
				ImGui::InputFloat("Z", &sceneGameObjects[i]->transform.Scale.z, 1.0f, 10.0f, "%.1f");
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Advanced"))
			{
				//Deactivate or Destroy GameObject
				ImGui::Checkbox("Active", &sceneGameObjects[i]->IsActive);
				if (ImGui::Button("Destroy"))
				{
					this->Destroy(sceneGameObjects[i]);
				}

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
		
		//Update GameObejects
		sceneGameObjects[i]->Update();
	}
	ImGui::End();
}

void Scene::DeInit()
{
	//Deinit the GameObjects
	for (GameObject* obj : sceneGameObjects)
	{
		obj->DeInit();
	}
}

GameObject* Scene::Instantiate(const char* _name)
{
	//Create new GameObject
	GameObject* obj = new GameObject(_name);
	//Add to Scene GameObjects
	sceneGameObjects.push_back(obj);

	return obj;
}

void Scene::InitialzeGameObject(GameObject* _toinit)
{
	//Awake and Start the given GameObjects
	_toinit->Awake(p_d3dDevice, p_d3dDeviceContext, p_deltaTime);
	_toinit->Start();
}


void Scene::Destroy(GameObject* _obj)
{
	//Remove the GameObject from the List
	sceneGameObjects.erase(std::remove(sceneGameObjects.begin(), sceneGameObjects.end(), _obj), sceneGameObjects.end());
	_obj = nullptr;
}
