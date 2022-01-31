#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Utils.h"
#include "Mesh.h"
#include "Camera.h"
#include "Time.h"
#include "Material.h"
#include "Light.h"

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

	//Create Mesh/Object
	Mesh mesh = {};
	error = mesh.Init(d3d.GetDevice());
	CheckError(error);

	//Create Cam
	Camera camera = {};
	error = camera.Init(width, height);
	CheckError(error);

	//Set Up Time
	Time time = {};
	error = time.Init();
	CheckError(error);

	//Create Material
	Material material = {};
	error = material.Init(d3d.GetDevice(), TEXT("HUHU.jpg"));
	CheckError(error);

	//Create Light
	Light::LightData lightData = {};
	lightData.LightDirection = { -1.0f, -1.0f, 1.0f};
	lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	lightData.LightIntensity = 10.0f;

	Light light = {};
	error = light.Init(d3d.GetDevice(), lightData);
	CheckError(error);

	//Run App
	while (window.Update())
	{
		time.Update();

		//Update Objs
		mesh.Update(time.GetDeltaTime());

		//Draw Objs
		d3d.BeginScene(0,0,0);

		camera.Update(time.GetDeltaTime());
		material.Render(d3d.GetDeviceContext(), mesh.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix());
		light.Render(d3d.GetDeviceContext());
		mesh.Render(d3d.GetDeviceContext());

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