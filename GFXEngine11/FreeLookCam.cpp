#include "FreeLookCam.h"
#include "imgui/imgui.h"

INT FreeLookCam::AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	p_deltaTime = _p_dt;
	return 0;
}

void FreeLookCam::StartComponent()
{
	//p_cam = (Camera*)gameObject->GetComponent(EComponentTypes::C_Camera);
}

void FreeLookCam::UpdateComponent()
{
	XMFLOAT3 input = { 0,0,0 };

	if (GetAsyncKeyState('W') & 0x8000)
	{
		input.x += this->gameObject->transform.LocalForward.x;
		input.y += this->gameObject->transform.LocalForward.y;
		input.z += this->gameObject->transform.LocalForward.z;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		input.x -= this->gameObject->transform.LocalRight.x;
		input.y -= this->gameObject->transform.LocalRight.y;
		input.z -= this->gameObject->transform.LocalRight.z;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		input.x -= this->gameObject->transform.LocalForward.x;
		input.y -= this->gameObject->transform.LocalForward.y;
		input.z -= this->gameObject->transform.LocalForward.z;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		input.x += this->gameObject->transform.LocalRight.x;
		input.y += this->gameObject->transform.LocalRight.y;
		input.z += this->gameObject->transform.LocalRight.z;
	}

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		input.x += this->gameObject->transform.LocalUp.x;
		input.y += this->gameObject->transform.LocalUp.y;
		input.z += this->gameObject->transform.LocalUp.z;
	}

	if (GetAsyncKeyState('E') & 0x8000)
	{
		input.x -= this->gameObject->transform.LocalUp.x;
		input.y -= this->gameObject->transform.LocalUp.y;
		input.z -= this->gameObject->transform.LocalUp.z;
	}

	this->gameObject->transform.AddPosition(input.x * camMovementSpeed * *p_deltaTime, input.y * camMovementSpeed * *p_deltaTime, input.z * camMovementSpeed * *p_deltaTime);

	//globalen directions localisieren -> local right etc
	//Up & down inputs * local Right
	//left right inputs * local up

	input = { 0,0,0 };

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		input.x -= this->gameObject->transform.LocalRight.x;
		input.y -= this->gameObject->transform.LocalRight.y;
		input.z -= this->gameObject->transform.LocalRight.z;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		input.x += this->gameObject->transform.LocalRight.x;
		input.y += this->gameObject->transform.LocalRight.y;
		input.z += this->gameObject->transform.LocalRight.z;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		input.x += this->gameObject->transform.LocalUp.x;
		input.y += this->gameObject->transform.LocalUp.y;
		input.z += this->gameObject->transform.LocalUp.z;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		input.x -= this->gameObject->transform.LocalUp.x;
		input.y -= this->gameObject->transform.LocalUp.y;
		input.z -= this->gameObject->transform.LocalUp.z;
	}

	this->gameObject->transform.AddRotation(input.x * camRotationSpeed * *p_deltaTime, input.y * camRotationSpeed * *p_deltaTime, input.z * camRotationSpeed * *p_deltaTime);
}

void FreeLookCam::DeInitComponent()
{
}
