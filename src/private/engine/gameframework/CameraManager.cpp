#include "engine/gameframework/CameraManager.h"

void CameraManager::AddCamera(const std::string& key, Camera* camera)
{
	m_cameras.insert_or_assign(key, camera);
}

Camera* CameraManager::GetCamera(const std::string& key)
{
	if (m_cameras.find(key) == m_cameras.end())
	{
		return nullptr;
	}
	return m_cameras[key];
}