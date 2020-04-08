#pragma once

#include <SFML/System/Clock.hpp>

class DeltaTime
{
public:
	DeltaTime() = default;

	void Update()
	{
		sf::Time deltaTime = m_deltaClock.restart();
		m_deltaTime = deltaTime.asSeconds();
	}

	const float& GetDeltaTime()
	{
		return m_deltaTime;
	}

private:
	sf::Clock m_deltaClock;
	float m_deltaTime;
};