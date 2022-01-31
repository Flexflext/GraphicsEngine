#pragma once
#include <Windows.h>
#include <chrono>

using namespace std;

#define TIMEPOINT chrono::high_resolution_clock::time_point //okay but not nice for data types
#define NOW chrono::high_resolution_clock::now()
typedef chrono::high_resolution_clock::time_point time_point;
typedef chrono::duration<float> duration;

class Time
{
public:
	INT Init();
	void Update();
	void DeInit();
	
	FLOAT* GetDeltaTime() { return &deltaTime; }

private:
	time_point lastTimeStamp = {};

	FLOAT deltaTime = 0.0f;
	FLOAT totalTime = 0.0f;
	UINT fps = 0;
	UINT lastFps = 0;
	FLOAT fpsTime = 0.0f;

};

