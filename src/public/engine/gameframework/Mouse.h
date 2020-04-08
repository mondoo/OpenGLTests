#pragma once

#include "engine/graphics/Renderer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

class Mouse
{
public:
	Mouse() = default;

	void SetCenter(Renderer& renderer)
	{
		sf::Vector2u windowCenterUnsigned = renderer->getSize() / 2u;
		m_windowCenter = { (int)windowCenterUnsigned.x, (int)windowCenterUnsigned.y };
		LockPosition(renderer);
		m_mouseLast = sf::Mouse::getPosition(*renderer.GetWindow());

	}

	void LockPosition(Renderer& renderer)
	{
		if (renderer->hasFocus())
		{
			sf::Mouse::setPosition(m_windowCenter, *renderer.GetWindow());
		}
	}

	sf::Vector2i Update(Renderer& renderer)
	{
		sf::Vector2i mouseCurrent = sf::Mouse::getPosition(*renderer.GetWindow());
		if (mouseCurrent != m_mouseLast && renderer->hasFocus())
		{
			m_mouseChange = m_mouseLast - mouseCurrent;
			LockPosition(renderer);
			m_mouseLast = m_windowCenter;
			return m_mouseChange;
		}

		return { 0, 0 };
	}

private:
	sf::Vector2i m_windowCenter;
	sf::Vector2i m_mouseLast;
	sf::Vector2i m_mouseChange;
};