#pragma once

#include "Singleton.h"

#include <memory>

#include "engine/graphics/Renderer.h"
#include "engine/gameframework/DeltaTime.h"
#include "engine/gameframework/CameraManager.h"
#include "engine/gameframework/Mouse.h"

class Root : public Singleton<Root>
{
public:
	Root()
	{
		m_renderer = &Singleton<Renderer>::GetInstance();
		m_camera = &Singleton<CameraManager>::GetInstance();
		m_mouse = &Singleton<Mouse>::GetInstance();
		m_deltaTime = &Singleton<DeltaTime>::GetInstance();
	}

	~Root()
	{
		m_renderer = nullptr;
		delete m_renderer;
		m_camera = nullptr;
		delete m_camera;
		m_mouse = nullptr;
		delete m_mouse;
		m_deltaTime = nullptr;
		delete m_deltaTime;
	}

	Renderer* GetRenderer() { return m_renderer; }
	CameraManager* GetCameraManager() { return m_camera; }
	Mouse* GetMouse() { return m_mouse; }
	DeltaTime* GetDeltaTime() { return m_deltaTime; }

private:
	Renderer* m_renderer;
	CameraManager* m_camera;
	Mouse* m_mouse;
	DeltaTime* m_deltaTime;
};
