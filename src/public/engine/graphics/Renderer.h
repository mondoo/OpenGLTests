#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <GL/glew.h>

class Renderer
{
public:
	Renderer() = default;

	Renderer(sf::Vector2<int> inSize, const sf::String& inTitle, sf::ContextSettings settings, sf::Uint32 style = sf::Style::Default);

	void InitRenderer(sf::Vector2<int> inSize, const sf::String& inTitle, sf::ContextSettings settings, sf::Uint32 style = sf::Style::Default);

	~Renderer();

	sf::RenderWindow* operator->() const
	{
		return &*m_Renderer;
	}

	int InitialiseGL();

	void Terminate();

	void Clear();

	void setVerticalSyncEnabled(bool isEnable)
	{
		m_Renderer->setVerticalSyncEnabled(true);
	}
	
	void setMouseCursorVisible(bool isVisible)
	{
		m_Renderer->setMouseCursorVisible(false);
	}

	sf::RenderWindow* GetWindow();

private:
	sf::RenderWindow* m_Renderer;

	bool m_isUsingGL = false;
};
