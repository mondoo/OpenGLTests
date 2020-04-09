#include "engine/gameframework/Mouse.h"

#include <SFML/Window/Mouse.hpp>

void Mouse::SetCenter(sf::RenderWindow* renderer)
{
	sf::Vector2u windowCenterUnsigned = renderer->getSize() / 2u;
	m_windowCenter = { (int)windowCenterUnsigned.x, (int)windowCenterUnsigned.y };
	LockPosition(renderer);
	m_mouseLast = sf::Mouse::getPosition(*renderer);

}

void Mouse::LockPosition(sf::RenderWindow* renderer)
{
	if (renderer->hasFocus())
	{
		sf::Mouse::setPosition(m_windowCenter, *renderer);
	}
}

sf::Vector2i Mouse::Update(sf::RenderWindow* renderer)
{
	sf::Vector2i mouseCurrent = sf::Mouse::getPosition(*renderer);
	if (mouseCurrent != m_mouseLast && renderer->hasFocus())
	{
		m_mouseChange = m_mouseLast - mouseCurrent;
		LockPosition(renderer);
		m_mouseLast = m_windowCenter;
		return m_mouseChange;
	}

	return { 0, 0 };
}