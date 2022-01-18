#include "Time.h"
#include <string>

INT Time::Init()
{
	lastTimeStamp = NOW;
	return 0;
}

void Time::Update()
{
	time_point now = NOW;
	duration diff = now - lastTimeStamp;
	deltaTime = diff.count();
	totalTime += deltaTime;
	lastTimeStamp = now;

	fps++;
	fpsTime += deltaTime;

#if _DEBUG
#if UNICODE
	wstring output = to_wstring(deltaTime);
#else // UNICODE
	string output = to_string(deltaTime);
#endif // UNICODE
	output = TEXT("DeltaTime:") + output + TEXT(" s\n");
	OutputDebugString(output.c_str());

	//print fps extrapolated
#if UNICODE
	output = to_wstring(1.0f / deltaTime);
#else // UNICODE
	output = to_string(1.0f / deltaTime);
#endif // UNICODE
	output = TEXT("FPS Extrapolated:") + output + TEXT("\n");
	OutputDebugString(output.c_str());

	if (fpsTime >= 1.0f)
	{
		lastFps = fps;
		fps = 0;
		fpsTime -= 1.0f;
	}

	//print fps commultated
#if UNICODE
	output = to_wstring(lastFps);
#else // UNICODE
	output = to_string(lastFps);
#endif // UNICODE
	output = TEXT("FPS Commulated:") + output + TEXT("\n");
	OutputDebugString(output.c_str());

	


#endif // _DEBUG

}

void Time::DeInit()
{
}
