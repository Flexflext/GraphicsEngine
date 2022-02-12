#pragma once
#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Mesh.h"
#include "Camera.h"
#include "Time.h"
#include "Material.h"
#include "Light.h"
#include "AllCameras.h"
#include "Utils.h"
#include "ImguiManager.h"
#include "ObjectImporter.h"
#include "imgui/imgui.h"
#include "TextureLightingProperties.h"



int WINAPI WinMain(HINSTANCE _hinstance, HINSTANCE _hprevinstance, LPSTR _lpcmdline, int _ncmdshow)
{
	ImguiManager imGui = {};

	//Create Window
	Window window = {};
	INT error = window.Init(_hinstance, WindowWidth, WindowHeight);
	CheckError(error);

	//Conection to DirectX
	D3D d3d = {};
	error = d3d.Init(window.GetWindowHandle(), WindowWidth, WindowHeight, isFullScreen);
	CheckError(error);
	window.d3d = d3d;

	//Set Up Time
	Time time = {};
	error = time.Init();
	CheckError(error);

	std::vector<GameObject*> allGameObjects;

	GameObject cameraObj = {};
	allGameObjects.push_back(&cameraObj);
	cameraObj.AddComponent(EComponentTypes::C_Camera);
	cameraObj.AddComponent(EComponentTypes::CS_FreeLookCam);
	//cameraObj.transform.SetRotation(0, 90, 0);


	GameObject gm = {};
	allGameObjects.push_back(&gm);
	Mesh* meh = (Mesh*)gm.AddComponent(EComponentTypes::C_Mesh);

	ObjectImporter imp = {};

	imp.Import3DAsset("Models\\Robot.fbx", meh);

	TextureLightingProperties props = { TEXT("Textures\\Robot.png") };
	meh->MyMaterial->SetMaterial(&props);


	//meh = gm.GetComponent<Mesh>();

	

	

	Light::LightData lightData = {};
	lightData.LightDirection = { -1.0f, -1.0f, 1.0f };
	lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	lightData.LightIntensity = 1.0f;

	Light* lamp = (Light*)gm.AddComponent(EComponentTypes::C_Light);
	lamp->SetLight(lightData);

	gm.transform.SetPosition(0, 0, 5);
	gm.transform.SetRotation(0, 0, 0);

	

	GameObject obj = {};
	allGameObjects.push_back(&obj);
	Mesh* mesh = (Mesh*)obj.AddComponent(EComponentTypes::C_Mesh);

	imp.Import3DAsset("Models\\FinalBaseMesh.obj", mesh);

	TextureLightingProperties prop = { TEXT("Textures\\HUHU.jpg") };
	mesh->MyMaterial->SetMaterial(&prop);


	//Initialize GameObjects
	for (GameObject* obj : allGameObjects)
	{
		obj->Awake(d3d.GetDevice(), d3d.GetDeviceContext(), time.GetDeltaTime());
		CheckError(error);
	}
	for (GameObject* obj : allGameObjects)
	{
		obj->Start();
	}


	//Run App
	while (window.Update())
	{
		imGui.Update();
		time.Update();
		d3d.BeginScene(1,1,1);
		

		for (GameObject* obj : allGameObjects)
		{
			obj->Update();
		}


		/*if (ImGui::Begin("Model Parmaters | After Method"))
		{
			for (size_t i = 0; i < vertSize; i++)
			{
				ImGui::Text("Pos %.1f %.1f %.1f", p_vertecies[i].position.x, p_vertecies[i].position.y, p_vertecies[i].position.z);
			}
		}
		ImGui::End();*/


		imGui.EndUpdate();
		d3d.EndScene();

		
	}

	//Tidy Up
	for (GameObject* obj : allGameObjects)
	{
		obj->DeInit();
	}

	d3d.DeInit();
	window.DeInit();
	time.DeInit();

	return 0;
}