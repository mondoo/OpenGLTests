#pragma once

#include "Engine.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace Global
{
	static Engine engine;

	Engine& GetEngine();

	Renderer& GetRenderer();

	sf::RenderWindow* GetWindow();

	bool IsOpen();

	const float& GetDeltaTime();

	entt::registry& GetECS();

	template<typename T = Texture>
	T* FindAsset(char* name)
	{
		return GetEngine().GetResourceManager()->Find<T>(name);
	}

	template<typename T = Texture>
	void FilterAssetsByType(std::vector<T*>& collection, ResourceType type)
	{
		GetEngine().GetResourceManager()->FilterByType<T>(collection, type);
	}
}