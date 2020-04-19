#pragma once

#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

struct InputDirectionFlags
{
	InputDirectionFlags() = default;

	unsigned int Forwards:1;
	unsigned int Backwards:1;
	unsigned int Left:1;
	unsigned int Right:1;

	void Reset()
	{
		Forwards = 0;
		Backwards = 0;
		Left = 0;
		Right = 0;
	}
};

struct InputComponent
{
	InputComponent() = default;
	InputComponent(bool isLocked)
		: m_isLocked(isLocked)
	{}

	void SetCenter(sf::RenderWindow* renderer)
	{
		sf::Vector2u windowCenterUnsigned = renderer->getSize() / 2u;
		m_windowCenter = { (int)windowCenterUnsigned.x, (int)windowCenterUnsigned.y };
		LockPosition(renderer);
		m_mouseLast = sf::Mouse::getPosition(*renderer);

	}

	void LockPosition(sf::RenderWindow* renderer)
	{
		if (renderer->hasFocus())
		{
			sf::Mouse::setPosition(m_windowCenter, *renderer);
		}
	}

	void Update(sf::RenderWindow* renderer)
	{
		UpdateKeyboard();
		UpdateMouse(renderer);
	}

	void UpdateMouse(sf::RenderWindow* renderer)
	{
		sf::Vector2i mouseCurrent = sf::Mouse::getPosition(*renderer);
		if (mouseCurrent != m_mouseLast && renderer->hasFocus())
		{
			m_mouseChange = m_mouseLast - mouseCurrent;
			LockPosition(renderer);
			m_mouseLast = m_windowCenter;
		}
		else
		{
			m_mouseChange = { 0,0 };
		}
	}

	void UpdateKeyboard()
	{
		m_direction.Reset();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_direction.Forwards = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_direction.Left = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_direction.Backwards = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_direction.Right = 1;
		}
	}

	InputDirectionFlags GetDirection()
	{
		return m_direction;
	}
	
	sf::Vector2i GetMouseChange()
	{
		return m_mouseChange;
	}

private:
	bool m_isLocked = false;

	sf::Vector2i m_windowCenter;
	sf::Vector2i m_mouseLast;
	sf::Vector2i m_mouseChange;

	InputDirectionFlags m_direction;
};