#include "engine/ECS/Components/InputComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

InputComponent::InputComponent(bool isLocked)
	: m_isLocked(isLocked)
{}

void InputComponent::SetCenter(sf::RenderWindow* renderer)
{
	sf::Vector2u windowCenterUnsigned = renderer->getSize() / 2u;
	m_windowCenter = { (int)windowCenterUnsigned.x, (int)windowCenterUnsigned.y };
	LockPosition(renderer);
	m_mouseLast = sf::Mouse::getPosition(*renderer);

}

void InputComponent::LockPosition(sf::RenderWindow* renderer)
{
	if (renderer->hasFocus())
	{
		sf::Mouse::setPosition(m_windowCenter, *renderer);
	}
}

void InputComponent::Update(sf::RenderWindow* renderer)
{
	UpdateKeyboard();
	UpdateMouse(renderer);
}

void InputComponent::UpdateMouse(sf::RenderWindow* renderer)
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

void InputComponent::UpdateKeyboard()
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

InputDirectionFlags InputComponent::GetDirection()
{
	return m_direction;
}

sf::Vector2i InputComponent::GetMouseChange()
{
	return m_mouseChange;
}