#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Utils.h"
#include "Mesh.h"
#include "Camera.h"
#include "Time.h"
#include "Material.h"

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

	d3d.GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	d3d.GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	d3d.GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

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

	//Run App
	while (window.Update())
	{
		time.Update();

		//Update Objs
		mesh.Update(time.GetDeltaTime());

		//Draw Objs
		d3d.BeginScene(D3DCOLOR_XRGB(0, 0, 0));

		camera.Render(d3d.GetDevice());
		mesh.Render(d3d.GetDevice());

		d3d.EndScene();
	}

	//Tidy Up
	material.DeInit();
	camera.DeInit();
	mesh.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}