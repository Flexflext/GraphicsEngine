#include "FreeLookCam.h"
#include "imgui/imgui.h"

INT FreeLookCam::AwakeComponent(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt)
{
	p_deltaTime = _p_dt;
	return 0;
}

void FreeLookCam::StartComponent()
{
	p_cam = (Camera*)gameObject->GetComponent(EComponentTypes::C_Camera);
}

void FreeLookCam::UpdateComponent()
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		this->gameObject->transform.AddPosition(0, 0, camMovementSpeed * *p_deltaTime);
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		this->gameObject->transform.AddPosition(-camMovementSpeed * *p_deltaTime, 0, 0);
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		
		this->gameObject->transform.AddPosition(0, 0, -camMovementSpeed * *p_deltaTime);
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		this->gameObject->transform.AddPosition(camMovementSpeed * *p_deltaTime, 0, 0);
	}

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		this->gameObject->transform.AddPosition(0, camMovementSpeed * *p_deltaTime, 0);
	}

	if (GetAsyncKeyState('E') & 0x8000)
	{
		this->gameObject->transform.AddPosition(0, -camMovementSpeed * *p_deltaTime, 0);
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		this->gameObject->transform.AddRotation(camRotationSpeed * *p_deltaTime, 0, 0);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		this->gameObject->transform.AddRotation(-camRotationSpeed * *p_deltaTime, 0, 0);
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		this->gameObject->transform.AddRotation(0,camRotationSpeed * *p_deltaTime, 0);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		this->gameObject->transform.AddRotation(0, -camRotationSpeed * *p_deltaTime, 0);
	}

	if (ImGui::Begin("Position Parmeters"))
	{
		ImGui::Text("Position <X>: %.1f", this->gameObject->transform.Position.x);
		ImGui::Text("Position <Y>: %.1f", this->gameObject->transform.Position.y);
		ImGui::Text("Position <Z>: %.1f", this->gameObject->transform.Position.z);
	}
	ImGui::End();
	if (ImGui::Begin("Roatation Parmeters"))
	{
		ImGui::Text("Rotation <X>: %.1f", this->gameObject->transform.Rotation.x);
		ImGui::Text("Rotation <Y>: %.1f", this->gameObject->transform.Rotation.y);
		ImGui::Text("Rotation <Z>: %.1f", this->gameObject->transform.Rotation.z);
	}
	ImGui::End();
}

void FreeLookCam::DeInitComponent()
{
}
