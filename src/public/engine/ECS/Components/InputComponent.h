#pragma once

#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class sf::RenderWindow;

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
	InputComponent(bool isLocked);

	void SetCenter(sf::RenderWindow* renderer);

	void LockPosition(sf::RenderWindow* renderer);

	void Update(sf::RenderWindow* renderer);

	void UpdateMouse(sf::RenderWindow* renderer);

	void UpdateKeyboard();

	InputDirectionFlags GetDirection();
	
	sf::Vector2i GetMouseChange();

private:
	bool m_isLocked = false;

	sf::Vector2i m_windowCenter;
	sf::Vector2i m_mouseLast;
	sf::Vector2i m_mouseChange;

	InputDirectionFlags m_direction;
};