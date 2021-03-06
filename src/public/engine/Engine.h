#pragma once

#include "engine/system/Singleton.h"
#include "engine/system/Root.h"
#include "engine/gameframework/entt.hpp"

class Engine : public Singleton<Engine>
{
public:
	Engine();

	~Engine();

	void Init();

	void Tick();

	const float& GetDeltaTime();

	Root* GetRoot();

	Renderer& GetRenderer();

	sf::RenderWindow* GetWindow();

	entt::registry& GetECS();

	ResourceManager* GetResourceManager();

private:
	Root* m_root;
	entt::registry ECS;
};