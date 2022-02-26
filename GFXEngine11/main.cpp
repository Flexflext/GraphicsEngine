//Main Script to Initialize the Different Components and Set Up the Scene
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
#include "ReflectionNormalShaderProperties.h"
#include "DynamicCubemap.h"
#include "ReflectionProbeManager.h"
#include "FreeLookCam.h"
#include "ConstantBufferTypes.h"
#include "SkyBoxShaderProperties.h"



int WINAPI WinMain(HINSTANCE _hinstance, HINSTANCE _hprevinstance, LPSTR _lpcmdline, int _ncmdshow)
{
#pragma region Initiation
	 
	// Create the IMgUI Manager
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

#pragma endregion

	//-> Set up the Scene Object
	Scene scene = { d3d->GetDevice(), d3d->GetDeviceContext(), time.GetDeltaTime()};

#pragma region Scene Initialization

	//-> DirectionalLight GameObject
	GameObject* light = scene.Instantiate("Directional Light");

	//-> LightData for the Directional Light
	LightData lightData = {};
	lightData.LightDirection = { -1.0f, -1.0f, 1.0f };
	lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	lightData.LightIntensity = 1.0f;
	lightData.AmbientLight = { 0.05f, 0.05f, 0.05f, 0.05f };

	//-> Light Component for DirectionalLight GameObejct
	Light* lamp = light->AddComponent<Light>();
	lamp->SetLight(lightData);

	//-> SkyBox GameObject
	GameObject* p_skyBox = scene.Instantiate("SkyBox");
	//-> Add Mesh Component
	Mesh* sky = p_skyBox->AddComponent<Mesh>();
	//-> Set Mesh
	sky->LoadMesh("Models\\3d-model.fbx", 0, 0.01f);
	//-> Set Material
	SkyBoxShaderProperties properties = { L"Textures\\misty_pines_Skybox.dds" };
	sky->SetMaterial(&properties);

	//-> Set Up Camera
	GameObject* cameraObj = scene.Instantiate("Cam");
	//-> Add Camera Component and Free-Look Cam
	cameraObj->AddComponent<Camera>();
	cameraObj->AddComponent<FreeLookCam>();

	//-> Set Up Mesh
	GameObject* gm = scene.Instantiate("Giant");

	//-> Set up Component
	Mesh* meh = gm->AddComponent<Mesh>();
	//-> Load Mesh and Set Material
	meh->LoadMesh("Models\\FinalBaseMesh.obj", 0, 1);
	SpecularLightingProperties props = { TEXT("Textures\\Robot.png"), {1}, {1,1,1,1}, {64} };
	meh->SetMaterial(&props);

	//-> Set Initial Position
	gm->transform.SetPosition(0, 0, 5);

	//-> Load GameObject Mesh
	GameObject* obj = scene.Instantiate("Human");
	Mesh* mesh = obj->AddComponent<Mesh>();

	//-> Get Component Method (Only to show that it works)
	mesh = obj->GetComponent<Mesh>();

	//-> Load Mesh Mesh
	mesh->LoadMesh("Models\\FinalBaseMesh.obj",0, 0.1f);
	//-> Set Different Shader
	ReflectionNormalShaderProperties prop = { TEXT("Textures\\Robot.png"), TEXT("Textures\\HUHU.jpg"),  TEXT("Textures\\misty_pines_Skybox.dds"), {0.1f}, {1,1,1,1}, {64} };
	mesh->SetMaterial(&prop);

	GameObject* obj2 = scene.Instantiate("Cow");
	Mesh* mesh2 = obj2->AddComponent<Mesh>();

	//-> Load Mesh Mesh
	mesh2->LoadMesh("Models\\spot_triangulated.obj", 0, 1.0f);
	//-> Set Different Shader
	NormalShaderProperties prop2 = { TEXT("Textures\\HUHU.jpg"), TEXT("Textures\\HUHU.jpg"), {0.1f}, {1,1,1,1}, {64} };
	mesh2->SetMaterial(&prop2);

	obj2->transform.SetPosition(5, 0, 5);
	obj2->transform.SetRotation(5, 90, 5);


	/*GameObject* reflection = scene.Instantiate("ReflectionSphere");
	DynamicCubemap* p_cubemap = reflection->AddComponent<DynamicCubemap>();

	ReflectionProbeManager::dynmaicCubeMap = p_cubemap;*/

#pragma endregion

	//Initialize GameObjects
	scene.Awake();
	scene.Start();

	//Run App
	while (window->Update())
	{
		//Update Start
		imGui.Update();
		time.Update();
		d3d->BeginScene(1,1,1);
		
		//-> Update all GameObects
		scene.Update();

		//Update End
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