#include "ImguiManager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

ImguiManager::ImguiManager()
{
	//Set up ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	//Set Docking Flag
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

ImguiManager::~ImguiManager()
{
	//DeInitialize the ImGUi
	ImGui::DestroyContext();
}

void ImguiManager::Update()
{
	//Set New Frame Update //-> Between Update and EndUpdate it ImGui Can be Used
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	/*static bool show_demo_window = true;
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}*/	
}

void ImguiManager::EndUpdate()
{
	//Set the End of the Frame Update
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


