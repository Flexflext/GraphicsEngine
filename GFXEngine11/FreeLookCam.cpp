#include "FreeLookCam.h"
#include "imgui/imgui.h"

INT FreeLookCam::AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	//-> Set DeltaTime
	p_deltaTime = _p_dt;
	return 0;
}

void FreeLookCam::StartComponent()
{
}

void FreeLookCam::UpdateComponent()
{
	XMFLOAT3 input = { 0,0,0 };

	//Add Forward Position Input
	if (GetAsyncKeyState('W') & 0x8000)
	{
		input.x += this->gameObject->transform.LocalForward.x;
		input.y += this->gameObject->transform.LocalForward.y;
		input.z += this->gameObject->transform.LocalForward.z;
	}

	//Add Left Position Input
	if (GetAsyncKeyState('A') & 0x8000)
	{
		input.x -= this->gameObject->transform.LocalRight.x;
		input.y -= this->gameObject->transform.LocalRight.y;
		input.z -= this->gameObject->transform.LocalRight.z;
	}

	//Add Backward Position Input
	if (GetAsyncKeyState('S') & 0x8000)
	{
		input.x -= this->gameObject->transform.LocalForward.x;
		input.y -= this->gameObject->transform.LocalForward.y;
		input.z -= this->gameObject->transform.LocalForward.z;
	}

	//Add Right Position Input
	if (GetAsyncKeyState('D') & 0x8000)
	{
		input.x += this->gameObject->transform.LocalRight.x;
		input.y += this->gameObject->transform.LocalRight.y;
		input.z += this->gameObject->transform.LocalRight.z;
	}

	//Add Up Position Input
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		input.x += this->gameObject->transform.LocalUp.x;
		input.y += this->gameObject->transform.LocalUp.y;
		input.z += this->gameObject->transform.LocalUp.z;
	}

	//Add Down Position Input
	if (GetAsyncKeyState('E') & 0x8000)
	{
		input.x -= this->gameObject->transform.LocalUp.x;
		input.y -= this->gameObject->transform.LocalUp.y;
		input.z -= this->gameObject->transform.LocalUp.z;
	}

	//Set the Position of the GameObject
	this->gameObject->transform.AddPosition(input.x * camMovementSpeed * *p_deltaTime, input.y * camMovementSpeed * *p_deltaTime, input.z * camMovementSpeed * *p_deltaTime);

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		ImVec2 vec = ImGui::GetMouseDragDelta(1);

		//globalen directions localisieren -> local right etc
		//Up & down inputs * local Right
		//left right inputs * local up

		//Reset Input
		input = { 0,0,0 };

		

		//Add Right Rotation Input
		if (vec.x > 10.0f)
		{
			input.x += this->gameObject->transform.LocalUp.x;
			input.y += this->gameObject->transform.LocalUp.y;
			input.z += this->gameObject->transform.LocalUp.z;
		}

		//Add Left Rotation Input
		if (vec.x < -10.0f)
		{
			input.x -= this->gameObject->transform.LocalUp.x;
			input.y -= this->gameObject->transform.LocalUp.y;
			input.z -= this->gameObject->transform.LocalUp.z;
		}


		//Set the Rotation of the GameObject
		this->gameObject->transform.AddRotation(0, input.y * camRotationSpeed * *p_deltaTime, 0/*input.z * camRotationSpeed * *p_deltaTime*/);
	}
}

void FreeLookCam::DeInitComponent()
{
}
