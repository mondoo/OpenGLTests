#include "engine/gameframework/DeltaTime.h"

void DeltaTime::Update()
{
	sf::Time deltaTime = m_deltaClock.restart();
	m_deltaTime = deltaTime.asSeconds();
}

const float& DeltaTime::GetDeltaTime()
{
	return m_deltaTime;
}
