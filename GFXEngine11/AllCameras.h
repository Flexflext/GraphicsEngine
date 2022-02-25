//Manager Class to Store all Cameras
#pragma once
#include <vector>

class Camera;
static class AllCameras
{
public:
	/// <summary>
	/// Get the First Camera of the Li´st
	/// </summary>
	/// <returns></returns>
	static Camera* GetMainCamera() { return *allCameras.begin(); }
	/// <summary>
	/// Add a Camera to the Camera List
	/// </summary>
	/// <param name="_cam"></param>
	static void AddCamera(Camera* _cam) { allCameras.push_back(_cam); }
	/// <summary>
	/// Remove a Camera from the List
	/// </summary>
	/// <param name="_cam"></param>
	static void RemoveCamera(Camera* _cam)
	{
		allCameras.erase(std::remove(allCameras.begin(), allCameras.end(), _cam), allCameras.end());
	};
	/// <summary>
	/// Clear all Cameras 
	/// </summary>
	static void ClearCameras() { allCameras.clear(); }

private:
	static std::vector<Camera*> allCameras;
};

