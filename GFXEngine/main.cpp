#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Utils.h"
#include "Mesh.h"

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

	d3d.GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	d3d.GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//Create Mesh/Object
	Mesh mesh = {};
	error = mesh.Init(d3d.GetDevice());
	CheckError(error);

	//Create Cam

	//Set Up Time

	//Create Material

	//Create Light

	//Run App
	while (window.Update())
	{
		//Update Objs
		mesh.Update(0.0f);

		//Draw Objs
		d3d.BeginScene(D3DCOLOR_XRGB(255, 255, 255));

		mesh.Render(d3d.GetDevice());

		d3d.EndScene();
	}

	//Tidy Up
	mesh.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}