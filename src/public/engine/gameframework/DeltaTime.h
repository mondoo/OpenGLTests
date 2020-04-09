#pragma once

#include <SFML/System/Clock.hpp>

class DeltaTime
{
public:
	DeltaTime() = default;

	void Update();

	const float& GetDeltaTime();

private:
	sf::Clock m_deltaClock;
	float m_deltaTime;
};