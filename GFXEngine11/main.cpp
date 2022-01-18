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

	//d3d.GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//d3d.GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//d3d.GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	//d3d.GetDevice()->SetRenderState(D3DRS_COLORVERTEX, FALSE);
	//d3d.GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	////Create Mesh/Object
	//Mesh mesh = {};
	//error = mesh.Init(d3d.GetDevice());
	//CheckError(error);

	////Create Cam
	//Camera camera = {};
	//error = camera.Init(width, height);
	//CheckError(error);

	//Set Up Time
	Time time = {};
	error = time.Init();
	CheckError(error);

	////Create Material
	//Material material = {};
	//error = material.Init(d3d.GetDevice(), TEXT("HUHU.jpg"));
	//CheckError(error);

	////Create Light
	//D3DLIGHT9 lightData = {};
	//lightData.Type = D3DLIGHT_DIRECTIONAL;
	////lightData.Direction = { -1.0f, -1.0f, 1.0f};
	//lightData.Position = { 0.0f, 0.0f, -0.5f};
	//lightData.Ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	//lightData.Diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	//lightData.Specular = { 1.0f, 0.0f, 1.0f, 1.0f };
	//lightData.Range = 10.0f;
	////Attenuation = a0 + a1 * distance + a2 * distance * distance
	//lightData.Attenuation0 = 1.0f; //Constant
	//lightData.Attenuation1 = 0.2f; //Linear
	//lightData.Attenuation2 = 0.1f; //Quadric

	//Light light = {};
	//error = light.Init(lightData);
	//CheckError(error);

	//Run App
	while (window.Update())
	{
		time.Update();

	//	//Update Objs
	//	mesh.Update(time.GetDeltaTime());

		//Draw Objs
		d3d.BeginScene(1,1,1);

	//	camera.Render(d3d.GetDevice());
	//	material.Render(d3d.GetDevice());
	//	light.Render(d3d.GetDevice());
	//	mesh.Render(d3d.GetDevice());

		d3d.EndScene();
	}

	//Tidy Up
	//light.DeInit();
	//material.DeInit();
	//camera.DeInit();
	//mesh.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}