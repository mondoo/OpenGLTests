#include "engine/Global.h"

Engine& Global::GetEngine()
{
	return engine;
}

Renderer& Global::GetRenderer()
{
	return engine.GetRenderer();
}

sf::RenderWindow* Global::GetWindow()
{
	return engine.GetWindow();
}

bool Global::IsOpen()
{
	return GetRenderer()->isOpen();
}

const float& Global::GetDeltaTime()
{
	return engine.GetDeltaTime();
}

entt::registry& Global::GetECS()
{
	return engine.GetECS();
}