#pragma once

#include "engine/graphics/Renderer.h"
#include <SFML/Graphics.hpp>

class Mouse
{
public:
	Mouse() = default;

	void SetCenter(sf::RenderWindow* renderer);
	void LockPosition(sf::RenderWindow* renderer);
	sf::Vector2i Update(sf::RenderWindow* renderer);

private:
	sf::Vector2i m_windowCenter;
	sf::Vector2i m_mouseLast;
	sf::Vector2i m_mouseChange;
};