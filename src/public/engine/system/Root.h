#pragma once

#include "Singleton.h"

#include <memory>

#include "engine/graphics/Renderer.h"
#include "engine/gameframework/DeltaTime.h"
#include "engine/gameframework/ResourceManager.h"

class Root : public Singleton<Root>
{
public:
	Root();
	~Root();

	Renderer* GetRenderer();
	DeltaTime* GetDeltaTime();
	ResourceManager* GetResourceManager();

private:
	Renderer* m_renderer;
	DeltaTime* m_deltaTime;
	ResourceManager* m_resourceManager;
};
