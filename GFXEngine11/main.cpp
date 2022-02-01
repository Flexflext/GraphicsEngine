#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Utils.h"
#include "Mesh.h"
#include "Camera.h"
#include "Time.h"
#include "Material.h"
#include "Light.h"
#include "GameObject.h"

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

	//Create Mesh/Object
	Mesh mesh = {};
	error = mesh.Init(d3d.GetDevice(), d3d.GetDeviceContext(), time.GetDeltaTime());
	CheckError(error);

	//Create Cam
	Camera camera = {};
	error = camera.Init(width, height);
	CheckError(error);

	//Create Material
	Material material = {};
	error = material.Init(d3d.GetDevice(), d3d.GetDeviceContext(), TEXT("HUHU.jpg"), mesh.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix());
	CheckError(error);

	//Create Light
	Light::LightData lightData = {};
	lightData.LightDirection = { -1.0f, -1.0f, 1.0f};
	lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	lightData.LightIntensity = 1.0f;

	Light light = {};
	error = light.Init(d3d.GetDevice(), d3d.GetDeviceContext(), lightData);
	CheckError(error);

	GameObject gm = {};
	gm.Init();

	//Run App
	while (window.Update())
	{
		time.Update();

		//Update Objs
		mesh.Update();

		//Draw Objs
		d3d.BeginScene(1,1,1);

		camera.Update();
		material.Render();
		light.Render();
		mesh.Render();

		d3d.EndScene();
	}

	//Tidy Up
	light.DeInit();
	material.DeInit();
	camera.DeInit();
	mesh.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}