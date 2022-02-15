#pragma once
#include <vector>;

class Camera;
static class AllCameras
{
public:
	static Camera* GetMainCamera() { return *allCameras.begin(); }
	static void AddCamera(Camera* _cam) { allCameras.push_back(_cam); }
	static void RemoveCamera(Camera* _cam)
	{
		allCameras.erase(std::remove(allCameras.begin(), allCameras.end(), _cam), allCameras.end());
	};
	static void ClearCameras() { allCameras.clear(); }

private:
	static std::vector<Camera*> allCameras;
};

