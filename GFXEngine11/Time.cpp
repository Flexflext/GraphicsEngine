#include "Time.h"
#include "Utils.h"
#include <string>
#include "imgui/imgui.h"

INT Time::Init()
{
	//Init last TimeStamp
	lastTimeStamp = NOW;

	return 0;
}

void Time::Update()
{
	//Set Time Parameters
	now = NOW;
	diff = now - lastTimeStamp;
	deltaTime = diff.count();
	totalTime += deltaTime;
	lastTimeStamp = now;
	
	//Add FPS to Counter
	fps++;
	fpsTime += deltaTime;
	//CurrentDeltaTime = deltaTime;

	//Set Flast FPS per Second
	if (fpsTime >= 1.0f)
	{
		lastFps = fps;
		fps = 0;
		fpsTime -= 1.0f;
	}

	//Set Simulation Paramters
	if (ImGui::Begin("Simulation Parmaters"))
	{
		ImGui::Text("TotalTime: %.1fs", totalTime);
		ImGui::Text("DeltaTime: %.4fs", deltaTime);
		ImGui::Text("FPS: %i/s", lastFps);
	}
	ImGui::End();
}

void Time::DeInit()
{
}
