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
#include "ReflectionShaderProperties.h"
#include "DynamicCubemap.h"
#include "ReflectionProbeManager.h"
#include "FreeLookCam.h"
#include "ConstantBufferTypes.h"
#include "SkyBoxShaderProperties.h"



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

	Scene scene = { d3d->GetDevice(), d3d->GetDeviceContext(), time.GetDeltaTime()};

	GameObject* light = scene.Instantiate("Directional Light");
	LightData lightData = {};
	lightData.LightDirection = { -1.0f, -1.0f, 1.0f };
	lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	lightData.LightIntensity = 1.0f;
	lightData.AmbientLight = { 0.05f, 0.05f, 0.05f, 0.05f };

	Light* lamp = light->AddComponent<Light>();
	lamp->SetLight(lightData);

	GameObject* p_skyBox = scene.Instantiate("SkyBox");
	Mesh* sky = p_skyBox->AddComponent<Mesh>();
	sky->LoadMesh("Models\\3d-model.fbx", 0, 0.01f);
	SkyBoxShaderProperties properties = { L"Textures\\misty_pines_Skybox.dds" };
	sky->SetMaterial(&properties);

	GameObject* cameraObj = scene.Instantiate("Cam");
	cameraObj->AddComponent<Camera>();
	cameraObj->AddComponent<FreeLookCam>();

	

	GameObject* gm = scene.Instantiate("Robot");
	Mesh* meh = gm->AddComponent<Mesh>();


	meh->LoadMesh("Models\\FinalBaseMesh.obj", 0, 1);
	TextureLightingProperties props = { TEXT("Textures\\Robot.png") };
	meh->SetMaterial(&props);

	gm->transform.SetPosition(0, 0, 5);
	gm->transform.SetRotation(0, 0, 0);

	GameObject* obj = scene.Instantiate("Human");
	Mesh* mesh = obj->AddComponent<Mesh>();

	mesh = obj->GetComponent<Mesh>();

	mesh->LoadMesh("Models\\FinalBaseMesh.obj",0, 0.1f);

	ReflectionShaderProperties prop = { TEXT("Textures\\Robot.png"), TEXT("Textures\\HUHU.jpg"), TEXT("Textures\\misty_pines_Skybox.dds"), {1}, {1,1,1,1}, {64} };
	mesh->SetMaterial(&prop);


	GameObject* reflection = scene.Instantiate("ReflectionSphere");
	DynamicCubemap* p_cubemap = reflection->AddComponent<DynamicCubemap>();

	ReflectionProbeManager::dynmaicCubeMap = p_cubemap;

	//Initialize GameObjects
	scene.Awake();
	scene.Start();


	//Run App
	while (window->Update())
	{
		imGui.Update();
		time.Update();
		d3d->BeginScene(1,1,1);
		


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