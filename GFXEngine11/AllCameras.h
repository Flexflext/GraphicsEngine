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
		/*int idx = -1;

		for (size_t i = 0; i < allCameras.size(); i++)
		{
			if (allCameras[i] == _cam)
			{
				idx = i;
				break;
			}
		}

		allCameras.erase()*/
	}
	static void ClearCameras() { allCameras.clear(); }

private:
	static std::vector<Camera*> allCameras;
};

