#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

template<typename T = sf::RenderWindow>
class Renderer
{
public:
	Renderer(sf::Vector2<int> inSize, const sf::String& inTitle, sf::ContextSettings settings, sf::Uint32 style = sf::Style::Default)
	{
		m_Renderer = new T(sf::VideoMode(inSize.x, inSize.y), inTitle, style, settings);
	}

	~Renderer()
	{
		m_Renderer = nullptr;
		delete m_Renderer;
	}

	T* operator->() const
	{
		return &*m_Renderer;
	}

	int InitialiseGL()
	{
		// Allow extension features
		glewExperimental = GL_TRUE;

		// Init GLEW
		if (glewInit() != GLEW_OK)
		{
			printf("GLEW init failed.");
			m_Renderer->close();
			return 0;
		}

		m_isUsingGL = true;
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		return 1;
	}

	void Terminate()
	{
		m_Renderer->close();
	}

	void Clear()
	{
		if (!m_isUsingGL)
		{
			return;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	T* GetWindow()
	{
		return m_Renderer;
	}

private:
	T* m_Renderer;

	bool m_isUsingGL = false;
};
