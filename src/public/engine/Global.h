#pragma once

#include "Engine.h"

namespace Global
{
	static Engine engine;

	static Engine& GetEngine()
	{
		return engine;
	}

	static Renderer& GetRenderer()
	{
		return engine.GetRenderer();
	}

	static sf::RenderWindow* GetWindow()
	{
		return engine.GetWindow();
	}

	static bool IsOpen()
	{
		return GetRenderer()->isOpen();
	}

	const float& GetDeltaTime()
	{
		return engine.GetDeltaTime();
	}

	entt::registry& GetECS()
	{
		return engine.GetECS();
	}
}