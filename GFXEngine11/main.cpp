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


int WINAPI WinMain(HINSTANCE _hinstance, HINSTANCE _hprevinstance, LPSTR _lpcmdline, int _ncmdshow)
{
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
	cameraObj.transform.SetRotation(0, 0, 0);

	GameObject gm = {};
	allGameObjects.push_back(&gm);
	gm.AddComponent(EComponentTypes::C_Mesh);
	Mesh* meh = (Mesh*)gm.GetComponent(EComponentTypes::C_Mesh);
	meh->SetMesh(nullptr, 0, nullptr, 0);
	meh->MyMaterial->SetMaterial(TEXT("HUHU.jpg"), EMaterials::TextureLighting);
	
	Light::LightData lightData = {};
	lightData.LightDirection = { -1.0f, -1.0f, 1.0f };
	lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	lightData.LightIntensity = 1.0f;

	Light* lamp = (Light*)gm.AddComponent(EComponentTypes::C_Light);
	lamp->SetLight(lightData);

	gm.transform.SetPosition(0, 0, 5);
	gm.transform.SetRotation(0, 0, 0);


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
		time.Update();
		d3d.BeginScene(1,1,1);


		//gm.transform.AddRotation(-5 * *time.GetDeltaTime(), 0, -5 * *time.GetDeltaTime());
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			cameraObj.transform.AddPosition(0, 0, -10 * *time.GetDeltaTime());
		}
		

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			cameraObj.transform.AddRotation(5 * *time.GetDeltaTime(), 0, 0);
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			cameraObj.transform.AddRotation(0, 5 * *time.GetDeltaTime(), 0);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			cameraObj.transform.AddRotation(0, 0, 5 * *time.GetDeltaTime());
		}
		

		for (GameObject* obj : allGameObjects)
		{
			obj->Update();
		}
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