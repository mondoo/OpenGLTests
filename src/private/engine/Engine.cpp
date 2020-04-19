#include "engine/Engine.h"

Engine::Engine()
	: m_root(new Root())
{
}

Engine::~Engine()
{
	m_root = nullptr;
	delete m_root;
}

void Engine::Init()
{
	Renderer* renderer = m_root->GetRenderer();
	sf::ContextSettings context(24, 8, 2, 3, 3);
	renderer->InitRenderer({ 1600, 1200 }, "Hello World!", context);
	renderer->setVerticalSyncEnabled(true);
	renderer->setMouseCursorVisible(false);
	if (!renderer->InitialiseGL())
	{
		renderer->Terminate();
		return;
	}

	ECS = entt::registry{};
}

void Engine::Loop()
{
	m_root->GetDeltaTime()->Update();
}

const float& Engine::GetDeltaTime()
{
	return m_root->GetDeltaTime()->GetDeltaTime();
}

Root* Engine::GetRoot()
{
	return m_root;
}

Renderer& Engine::GetRenderer()
{
	return *m_root->GetRenderer();
}

sf::RenderWindow* Engine::GetWindow()
{
	return m_root->GetRenderer()->GetWindow();
}

entt::registry& Engine::GetECS()
{
	return ECS;
}

ResourceManager* Engine::GetResourceManager()
{
	return m_root->GetResourceManager();
}