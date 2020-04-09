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
	Root();
	~Root();

	Renderer* GetRenderer();
	CameraManager* GetCameraManager();
	Mouse* GetMouse();
	DeltaTime* GetDeltaTime();

private:
	Renderer* m_renderer;
	CameraManager* m_camera;
	Mouse* m_mouse;
	DeltaTime* m_deltaTime;
};
