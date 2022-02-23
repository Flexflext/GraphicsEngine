//Script to Start the Timer
#pragma once
#include <Windows.h>
#include <chrono>

#define TIMEPOINT std::chrono::high_resolution_clock::time_point //okay but not nice for data types
#define NOW std::chrono::high_resolution_clock::now()
typedef std::chrono::high_resolution_clock::time_point time_point;
typedef std::chrono::duration<float> duration;

class Time
{
public:
	/// <summary>
	/// Initialize the Timer
	/// </summary>
	/// <returns></returns>
	INT Init();
	/// <summary>
	/// Update the Timer
	/// </summary>
	void Update();
	/// <summary>
	/// Deinitialize the Timer
	/// </summary>
	void DeInit();
	
	/// <summary>
	/// Get a Pointer to the Current DeltaTime
	/// </summary>
	/// <returns></returns>
	FLOAT* GetDeltaTime() { return &deltaTime; }

private:
	//->Time Vars
	time_point lastTimeStamp = {};

	FLOAT deltaTime = 0.0f;
	FLOAT totalTime = 0.0f;
	INT fps = 0;
	INT lastFps = 0;
	FLOAT fpsTime = 0.0f;

	time_point now = {};
	duration diff = {};
};

