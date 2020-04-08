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

	void AddCamera(const std::string& key, Camera* camera)
	{
		m_cameras.insert_or_assign(key, camera);
	}

	Camera* GetCamera(const std::string& key)
	{
		if (m_cameras.find(key) == m_cameras.end())
		{
			return nullptr;
		}
		return m_cameras[key];
	}

private:
	std::unordered_map<std::string, Camera*> m_cameras;
};