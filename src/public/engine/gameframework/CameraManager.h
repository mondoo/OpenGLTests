#pragma once

#include <unordered_map>
#include <string>
#include "engine/gameframework/Camera.h"

class CameraManager
{
public:
	CameraManager() = default;

	Camera* operator[](const std::string& key)
	{
		return GetCamera(key);
	}

	void AddCamera(const std::string& key, Camera* camera);

	Camera* GetCamera(const std::string& key);

private:
	std::unordered_map<std::string, Camera*> m_cameras;
};