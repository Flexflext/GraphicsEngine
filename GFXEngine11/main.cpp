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
#include "SpecularLightingProperties.h"
#include "Scene.h"
#include "NormalShaderProperties.h"



int WINAPI WinMain(HINSTANCE _hinstance, HINSTANCE _hprevinstance, LPSTR _lpcmdline, int _ncmdshow)
{
	ImguiManager imGui = {};

	//Create Window
	Window* window = Window::GetInstance();
	INT error = window->Init(_hinstance, WindowWidth, WindowHeight);
	CheckIntError(error);

	//Conection to DirectX
	D3D* d3d = D3D::GetInstance();
	error = d3d->Init(window->GetWindowHandle(), WindowWidth, WindowHeight, isFullScreen);
	CheckIntError(error);

	//Set Up Time
	Time time = {};
	error = time.Init();
	CheckIntError(error);

	Scene scene = { d3d->GetDevice(), d3d->GetDeviceContext(), time.GetDeltaTime() };

	GameObject* cameraObj = scene.Instantiate("Cam");
	cameraObj->AddComponent(EComponentTypes::C_Camera);
	cameraObj->AddComponent(EComponentTypes::CS_FreeLookCam);

	

	GameObject* gm = scene.Instantiate("Robot");
	Mesh* meh = (Mesh*)gm->AddComponent(EComponentTypes::C_Mesh);


	meh->LoadMesh("Models\\Robot.fbx", 0, 0.2f);
	SpecularLightingProperties props = { TEXT("Textures\\Robot.png"), {1}, {1,1,1,1}, {64} };
	meh->MyMaterial->SetMaterial(&props);
	

	Light::LightData lightData = {};
	lightData.LightDirection = { -1.0f, -1.0f, 1.0f };
	lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	lightData.LightIntensity = 1.0f;
	lightData.AmbientLight = { 0.05f, 0.05f, 0.05f, 0.05f };

	Light* lamp = (Light*)gm->AddComponent(EComponentTypes::C_Light);
	lamp->SetLight(lightData);

	gm->transform.SetPosition(0, 0, 5);
	gm->transform.SetRotation(0, 0, 0);

	GameObject* obj = scene.Instantiate("Human");
	Mesh* mesh = (Mesh*)obj->AddComponent(EComponentTypes::C_Mesh);

	//mesh = obj->GetComponent<Mesh>();

	mesh->LoadMesh("Models\\FinalBaseMesh.obj",0, 0.1f);

	NormalShaderProperties prop = { TEXT("Textures\\Robot.png"), TEXT("Textures\\HUHU.jpg"), {1}, {1,1,1,1}, {64} };
	mesh->MyMaterial->SetMaterial(&prop);


	//Initialize GameObjects
	scene.Awake();
	scene.Start();


	//Run App
	while (window->Update())
	{
		imGui.Update();
		time.Update();
		d3d->BeginScene(1,1,1);

		

		/*if (GetAsyncKeyState('G') & 0x8000)
		{
			GameObject* gmt = scene.Instantiate("Robot1");
			Mesh* mehh = (Mesh*)gmt->AddComponent(EComponentTypes::C_Mesh);
			mehh->LoadMesh("Models\\Robot.fbx", 0, 0.4f);
			NormalShaderProperties propd = { TEXT("Textures\\Robot.png"), TEXT("Textures\\HUHU.jpg"), {1}, {1,1,1,1}, {64} };
			mehh->MyMaterial->SetMaterial(&propd);
			scene.InitialzeGameObject(gmt);
		}*/
		




		scene.Update();
		imGui.EndUpdate();
		d3d->EndScene();
	}

	//Tidy Up
	scene.DeInit();
	d3d->DeInit();
	window->DeInit();
	time.DeInit();

	return 0;
}