#pragma once
#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Utils.h"
#include "Mesh.h"
#include "Camera.h"
#include "Time.h"
#include "Material.h"
#include "Light.h"
#include "AllCameras.h"

//typedef INT(D3D::* func)(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt);

int WINAPI WinMain(HINSTANCE _hinstance, HINSTANCE _hprevinstance, LPSTR _lpcmdline, int _ncmdshow)
{
	UINT width = 1024;
	UINT height = 768;
	BOOL isFullScreen = false;

	//Create Window
	Window window = {};
	INT error = window.Init(_hinstance, width, height);
	CheckError(error);

	//Conection to DirectX
	D3D d3d = {};
	error = d3d.Init(window.GetWindowHandle(), width, height, isFullScreen);
	CheckError(error);
	window.d3d = d3d;

	//Set Up Time
	Time time = {};
	error = time.Init();
	CheckError(error);

	//Create Cam
	Camera camera = {};
	error = camera.Init(width, height);
	CheckError(error);


	GameObject gm = {};

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

	gm.transform.SetPosition(1, 1, 0);
	gm.transform.SetRotation(90, 90, 0);

	error = gm.Awake(d3d.GetDevice(), d3d.GetDeviceContext(), time.GetDeltaTime());
	CheckError(error);
	gm.Start();



	

	//Run App
	while (window.Update())
	{
		time.Update();

		//Draw Objs
		d3d.BeginScene(1,1,1);

		camera.Update();
		gm.Update();

		d3d.EndScene();
	}

	//Tidy Up
	gm.DeInit();
	camera.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}